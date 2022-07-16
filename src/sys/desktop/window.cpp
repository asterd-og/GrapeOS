#include <sys/desktop/window.h>
#include <kernel/multiboot.h>
#include <sys/debug/dbg.h>
#include <sys/drivers/ps2/mouse.h>
#include <sys/lib/math.h>
#include <sys/mem/heap.h>
#include <sys/lib/string.h>
#include <sys/drivers/video/canvas.h>

void Window::create(int x, int y, int width, int height, char* name, void(*onUpdate)(Window*), int id) {
    multiboot_t* mboot=Multiboot::get();
    
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->name = name;
    this->canvas.init(this->x,
                      this->y,
                      this->width,
                      this->height,
                      (uint32_t)mboot->framebuffer_pitch,
                      (uint32_t)mboot->framebuffer_bpp);
    
    this->canvas.Clear(LIGHTGRAY);

    this->id = id;

    this->closeButton.create(this->x+this->width-10, this->y-10, 10, 10, BLACK, GRAY, WHITE, kernel_font, "X", Vbe);
    
    this->onUpdate=onUpdate;

    Dbg::printf("Window '%s' created successfully.\n", name);
}

void Window::update() {
    Vbe.DrawRectangleOutline(this->x-1, this->y-11, this->width+1, this->height+11, BLACK);
    Vbe.DrawFilledRectangle(this->x, this->y-10, this->width, 10, BLACK);
    Vbe.DrawString(this->x, this->y-9, this->name, WHITE, kernel_font);

    this->canvas.Update();
    this->onUpdate(this);

    this->closeButton.update();

    if (Mouse::isLeftPressed()) {
        if (Mouse::isWithin(this->x, this->y-8, this->width, 8)) {
            if (!this->moving) {
                this->moving=true;
                this->xo=Mouse::getX() - this->x;
                this->yo=Mouse::getY() - this->y;
            }
        }
    } else {
        if (this->moving) { this->moving=false; memcpy(Mouse::currentCursorData, Mouse::cur_normal, 13*11); }
    }

    if (this->moving) {
        // Mouse::currentCursorData = (uint8_t**)Mouse::cur_move;
        memcpy(Mouse::currentCursorData, Mouse::cur_move, 13*11);
        this->x = Clamp(Mouse::getX() - this->xo, 0, Vbe.width);
        this->y = Clamp(Mouse::getY() - this->yo, 8, Vbe.height); //8 = title bar height
        (&this->closeButton)->x = this->x + this->width - 10;
        (&this->closeButton)->y = this->y - 10;
        (&this->canvas)->x      = this->x;
        (&this->canvas)->y      = this->y;
    }
}