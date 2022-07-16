#include <sys/desktop/desktop.h>
#include <sys/drivers/video/canvas.h>
#include <sys/drivers/ps2/mouse.h>
#include <sys/drivers/ps2/kb.h>
#include <sys/desktop/elements/button.h>
#include <sys/desktop/elements/image.h>
#include <sys/desktop/elements/text.h>
#include <sys/lib/string.h>
#include <sys/hw/rtc.h>
#include <sys/desktop/wm.h>
#include <sys/mem/heap.h>

namespace Desktop {
    Bmp grape;
    Button start;

    Bmp banner;
    Image img;

    Window welcome;

    void Idle(Window*w) {
    }

    void init() {
        banner.load("./System/Textures/Welcome/Banner.bmp");
        welcome.create(150, 150, 180, 42+120, "Welcome", Idle, 1);
        img.create(0, 0, banner, welcome.canvas);

        grape.load("./System/Textures/Assets/Grape.bmp");
        start.create(0, 0, strlen("Start")*font_get_width(kernel_font), 9, BLACK, GRAY, WHITE, kernel_font, "Start", Vbe);
    }

    void update() {
        Rtc::read();
        Vbe.Clear(0x5F0F40);
        Vbe.DrawBmp(Vbe.width / 2 - grape.width, Vbe.height / 2 - grape.height, grape);

        Vbe.DrawFilledRectangle(0, 0, Vbe.width, 9, BLACK);
        start.update();
        Vbe.DrawFString((Vbe.width / 2 - (strlen("MM/DD/YYYY") * font_get_width(kernel_font))) + (strlen("Start")*font_get_width(kernel_font)),
                        1, SNOW, kernel_font, "%d/%d/%d", Rtc::month, Rtc::day, Rtc::year);
        
        Vbe.DrawFString((Vbe.width - (strlen("HH:MM") * font_get_width(kernel_font))),
                        1, SNOW, kernel_font, "%d:%d", Rtc::hour, Rtc::minute);
        
        Vbe.DrawRectangleOutline(10-1, 25-1, 150+1, 100+1, BLACK);
        Vbe.DrawFilledRectangle(10, 25, 150, 10, BLACK);
        Vbe.DrawString(12, 26, "Resources", WHITE, FONT_SYSTEM_8x8);
        Vbe.DrawFilledRectangle(10, 25+10, 150, 100, WHITE);

        Vbe.DrawFString(12, 25+10+5, BLACK, FONT_SYSTEM_8x8, "Used ram: %d MB\nFree ram: %d MB\nTotal ram: %d MB", Heap::mem_get_used_ram()/M, Heap::mem_get_free_ram()/M, Heap::mem_get_total_ram()/M);

        welcome.update();
    }
}