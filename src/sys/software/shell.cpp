#include <sys/software/shell.h>
#include <sys/drivers/video/vga.h>
#include <sys/drivers/ps2/kb.h>
#include <sys/lib/printf.h>
#include <sys/lib/string.h>

namespace Shell {
    char buff[512];
    int idx=0;

    void ver() {
        Console.writeLine("GShl [Version 0.1]\nMade by astrido\n");
    }

    void input() {
        uint32_t oldfg = Console.fg;
        Console.fg = VGA_COLOR_GREEN;
        Console.write("GShl> ");
        Console.fg = oldfg;
        oldfg = NULL;
    }

    void init() {
        Console.fg = VGA_COLOR_WHITE;
        Console.bg = VGA_COLOR_BLACK;
        Console.clear();
        ver();
        input();
    }

    void handleCmd() {
        if (!strcmp(buff, "astrido")) {
            Console.writeLine("A very smort guy.");
        } else if (!strcmp(buff, "grape")) {
            Console.writeLine("Best fruit ever.");
        } else {
            if (strlen(buff) > 1) Console.writeLine("Unknown command.");
        }
    }

    void handleKey(int32_t keycode, char ch) {
        switch (keycode) {
            case ENTER:
                Console.write("\n");
                handleCmd();
                memset(buff, 0, strlen(buff));
                idx = 0;
                input();
                break;
            case BACKSPACE:
                if (idx > 0) {
                    Console.write("\b \b");
                    idx--;
                    buff[idx]='\0';
                }
                break;
            default:
                Console.writeChar(ch);
                buff[idx] = ch;
                idx++;
                break;
        }
    }
}

/*int cx = 0;
    int cy = 0;
    font_t font;

    uint32_t fg = WHITE;
    uint32_t bg = BLACK;

    char buff[512];
    int idx=0;

    void DrawChar(char c) {
        switch (c) {
            case '\n':
                cx = 0;
                cy += font_get_height(font);
                break;
            case '\b':
                cx -= font_get_width(font);
                Vbe.DrawFilledRectangle(cx, cy, font_get_width(font), font_get_height(font), bg);
                break;
            default:
                Vbe.DrawChar(cx, cy, c, fg, font);
                cx += font_get_width(font);
                break;
        }
    }

    void DrawString(char* fmt, ...) {
        char* buf;
        va_list args;
        va_start(args, fmt);
        vasprintf(buf, fmt, args);
        va_end(args);
        while (*buf) {
            DrawChar(*buf);
            *buf++;
        }
    }

    void ver() {
        DrawString("GShl [Version 0.1]\nMade by astrido\n\n");
    }

    void input() {
        uint32_t oldfg = fg;
        fg = GREEN;
        DrawString("GShl> ");
        fg = oldfg;
        oldfg = NULL;
    }

    void init() {
        Vbe.Clear(bg);
        font = FONT_SYSTEM_8x8;
        ver();
        input();
    }

    void handleKey(int32_t keycode, char ch) {
        switch (keycode) {
            case ENTER:
                DrawString("\n%s\n", buff);
                memset(buff, 0, strlen(buff));
                idx = 0;
                input();
                break;
            case BACKSPACE:
                DrawChar('\b');
                break;
            default:
                DrawChar(ch);
                buff[idx] = ch;
                idx++;
                break;
        }
    }*/