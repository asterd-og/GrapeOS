#include <sys/drivers/ps2/mouse.h>
#include <sys/lib/gfx/bounds.h>
#include <sys/hw/pic.h>
#include <sys/drivers/video/canvas.h>
#include <sys/tables/idt/isr.h>
#include <sys/tables/idt/irq.h>
#include <sys/hw/io.h>
#include <sys/lib/string.h>

namespace Mouse {
    bounds_t Bounds;
    point_t Position;

    uint8_t Offset;
    uint8_t Buttons;
    uint8_t Cycle;
    uint8_t Buffer[3];

    uint8_t currentCursorData[13][11];

    ButtonState LeftPressed;
    ButtonState RightPressed;

    CursorType current_cursor;

    uint8_t cur_normal[13][11]={
        {1,1,0,0,0,0,0,0,0,0,0},
        {1,2,1,0,0,0,0,0,0,0,0},
        {1,2,2,1,0,0,0,0,0,0,0},
        {1,2,2,2,1,0,0,0,0,0,0},
        {1,2,2,2,2,1,0,0,0,0,0},
        {1,2,2,2,2,2,1,0,0,0,0},
        {1,2,2,2,2,2,1,0,0,0,0},
        {1,1,1,2,1,1,1,0,0,0,0},
        {0,0,1,2,2,1,0,0,0,0,0},
        {0,0,0,1,2,2,1,0,0,0,0},
        {0,0,0,0,1,2,2,1,0,0,0},
        {0,0,0,0,0,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
    };

    uint8_t cur_link[13][11]={
        {0,1,1,0,0,0,0,0,0,0,0},
        {1,2,2,1,0,0,0,0,0,0,0},
        {1,2,2,1,0,0,0,0,0,0,0},
        {1,2,2,1,1,1,1,1,0,0,0},
        {1,2,2,1,2,2,1,2,1,0,0},
        {1,2,2,1,2,2,1,2,2,1,0},
        {1,2,2,1,2,2,1,2,1,2,1},
        {1,2,2,1,2,2,1,2,1,2,1},
        {1,2,2,2,2,2,2,2,2,2,1},
        {1,2,2,2,2,2,2,2,2,2,1},
        {0,1,2,2,2,2,2,2,2,1,0},
        {0,0,1,2,2,2,2,2,1,0,0},
        {0,0,0,1,1,1,1,1,0,0,0},
    };

    uint8_t cur_move[13][11]={
        {0,0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,1,1,1,0,0,0,0},
        {0,0,0,1,2,1,2,1,0,0,0},
        {0,0,0,2,2,1,2,2,0,0,0},
        {0,0,1,2,2,1,2,2,1,0,0},
        {0,1,2,2,2,1,2,2,2,1,0},
        {1,1,1,1,1,1,1,1,1,1,1},
        {0,1,2,2,2,1,2,2,2,1,0},
        {0,0,1,2,2,1,2,2,1,0,0},
        {0,0,0,2,2,1,2,2,0,0,0},
        {0,0,0,1,2,1,2,1,0,0,0},
        {0,0,0,0,1,1,1,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0},
    };

    void wait(uint8_t a_type) {
        uint32_t _time_out=100000; //unsigned int
        if(a_type==0) {
            while(_time_out--) {
                if((io::inb(0x64) & 1)==1)
                {
                    return;
                }
            }
            return;
        }
        else {
            while(_time_out--) {
                if((io::inb(0x64) & 2)==0) {
                    return;
                }
            }
            return;
        }
    }

    void write(uint8_t a_write) //unsigned char
    {
        //Tell the mouse we are sending a command
        wait(1);
        io::outb(0x64, 0xD4);
        wait(1);
        //Finally write
        io::outb(0x60, a_write);
    }

    uint8_t read()
    {
        wait(0);
        return io::inb(0x60);
    }

    void OnMove(int8_t x, int8_t y)
    {
        // increment pos
        Position.X += x;
        Position.Y += y;
        // clamp inside bounds
        if (Position.X < Bounds.X) { Position.X = 0; }
        if (Position.Y < Bounds.Y) { Position.Y = 0; }
        if (Position.X >= Bounds.Width) { Position.X = Bounds.Width; }
        if (Position.Y >= Bounds.Height) { Position.Y = Bounds.Height; }
    }

    //Mouse functions
    void handler(registers_t* regs)
    {
        uint8_t status = io::inb(0x64);
        //static char Buffer[3];
        if ((!(status & 1)) == 1) { Cycle = 0; return; }
        if ((!(status & 2)) == 0) { Cycle = 0; return; }
        if (!(status & 0x20)) { Cycle = 0; return; }
        //uint8_t _cycle=0;
        switch (Cycle)
        {
            case 0:
            {
                Buffer[0] = read();
                Cycle++;
                break;
            }
            case 1:
            {
                Buffer[1] = read();
                Cycle++;
                break;
            }
            case 2:
            {
                Buffer[2] = read();
                OnMove(Buffer[1], -Buffer[2]);
                LeftPressed = (ButtonState)(Buffer[0] & 0b00000001);
                RightPressed = (ButtonState)((Buffer[0] & 0b00000010) >> 1);
                Cycle = 0;
                break;
            }
        }
        Pic::eoi(12);
    }

    uint8_t GetButtons() { return Buttons; }

    bool isLeftPressed() { return LeftPressed; }

    // check if right mouse button is down
    bool isRightPressed() { return RightPressed; }

    void SetBounds(int32_t x, int32_t y, int32_t w, int32_t h)
    {
        Bounds.X =  x;
        Bounds.Y = y;
        Bounds.Width = w - 1;
        Bounds.Height = h - 1;
    }

    void SetPosition(uint32_t x, uint32_t y) { Position.X = x; Position.Y = y; }

    // get boundary
    bounds_t GetBounds() { return Bounds; }
    // get positions
    point_t GetPosition() { return Position; }
    // get x position
    int32_t getX() { return Position.X; }
    // get y position
    int32_t getY() { return Position.Y; }

    void install(uint32_t scr_width, uint32_t scr_height)
    {
        // normal_cur=bitmap_load("./cursors/cursor_normal.bmp");
        Bounds.X=0; Bounds.Y=0;
        SetBounds(0, 0, scr_width, scr_height);
        Position.X=0; Position.Y=0;
        Offset=0;
        Buttons=0;
        LeftPressed=Released;
        RightPressed=Released;
        current_cursor=Default;

        // currentCursorData = (uint8_t**)cur_normal;
        memcpy(currentCursorData, cur_normal, 13*11);

        uint8_t _status;  //unsigned char
        //Enable the auxiliary mouse device
        wait(1);
        io::outb(0x64, 0xA8);

        //Enable the interrupts
        wait(1);
        io::outb(0x64, 0x20);
        wait(0);
        _status=(io::inb(0x60) | 2);
        wait(1);
        io::outb(0x64, 0x60);
        wait(1);
        io::outb(0x60, _status);

        // Tell the mouse to use default settings
        write(0xF6);
        read();  //Acknowledge

        // Enable the mouse
        write(0xF4);
        read();  //Acknowledge
        Irq::install_handler(12, handler);
    }

    void changeCursor(uint8_t** newCursor) {
        memcpy(currentCursorData, newCursor, 13*11);
    }

    void draw() {
        //vbe_DrawUChar((int)Position.X, (int)Position.Y, WHITE, 'Q');
        for (int y=0;y<13;y++) {
            for (int x=0;x<11;x++) {
                switch (currentCursorData[y][x]) {
                    case 1:
                        Vbe.SetPixel((int)Position.X+x, (int)Position.Y+y, BLACK);
                        break;
                    case 2:
                        Vbe.SetPixel((int)Position.X+x, (int)Position.Y+y, WHITE);
                        break;
                }
            }
        }
    }

    void set_cursor(CursorType cursor) {
        current_cursor=cursor;
    }

    bool isWithin(int x, int y, int width, int height) {
        if (getX() >= x && getX() <= x+width && getY() >= y && getY() <= y+height) return true;
        return false;
    }
}