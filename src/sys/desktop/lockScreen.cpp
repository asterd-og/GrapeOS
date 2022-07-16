#include <sys/desktop/lockScreen.h>
#include <sys/drivers/initrd/ramdisk.h>
#include <sys/drivers/video/canvas.h>
#include <sys/drivers/ps2/mouse.h>
#include <sys/lib/string.h>
#include <sys/hw/rtc.h>
#include <sys/desktop/elements/button.h>

namespace LockScreen {
    Bmp user;
    Bmp userHovered;
    bool locked = true;
    bool hovered = false;
    char* userName;

    Button unlock;

    void init() {
        user.load("./System/LockScreen/User.bmp");
        userHovered.load("./System/LockScreen/UserHovered.bmp");
        userName = (char*)Tar::fopen("./System/LockScreen/User.txt");
        unlock.create(15 + (64 / 2) - ((strlen("Unlock")*font_get_width(FONT_SYSTEM_8x8))/2) - 2, Vbe.height / 2 - 64 + (64 + 10), strlen("Unlock")*font_get_width(FONT_SYSTEM_8x8) + 4, 10, BLACK, LIGHTGRAY, WHITE, FONT_SYSTEM_8x8, "Unlock", Vbe);
    }

    void update() {
        while (locked) {
            Vbe.Clear(0x5F0F40);

            Rtc::read();

            Vbe.DrawFilledRectangle(0, 0, Vbe.width, 9, BLACK);
            Vbe.DrawFString((Vbe.width / 2 - (strlen("MM/DD/YYYY") * font_get_width(kernel_font))),
                            1, SNOW, kernel_font, "%d/%d/%d", Rtc::month, Rtc::day, Rtc::year);
        
            Vbe.DrawFString((Vbe.width - (strlen("HH:MM") * font_get_width(kernel_font))),
                            1, SNOW, kernel_font, "%d:%d", Rtc::hour, Rtc::minute);
            
            if (Mouse::isWithin(15, Vbe.height / 2 - 64, 64, 64)) hovered = true;
            else { if (hovered) hovered = false; }

            if (!hovered) Vbe.DrawBmp(15, Vbe.height / 2 - 64, user);
            else Vbe.DrawBmp(15, Vbe.height / 2 - 64, userHovered);

            Vbe.DrawString(15 + 64 + 5, Vbe.height / 2 - 64 + (64 / 2) - 8, userName, WHITE, FONT_SYSTEM_8x8);
            unlock.update();

            if (unlock.clicked) {
                locked = false;
            }

            Mouse::draw();

            Vbe.Update();
        }
    }
}