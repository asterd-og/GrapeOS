#pragma once

#include <stdint.h>
#include <stddef.h>
#include <sys/lib/gfx/aaf.h>
#include <sys/lib/gfx/fonts.h>
#include <sys/lib/gfx/colors.h>
#include <sys/gfx/tga.h>
#include <sys/gfx/bmp.h>
#include <sys/lib/printf.h>

class Base {
    public:
        uint32_t* buffer;
        uint32_t  pitch;
        uint32_t  bpp;
        uint32_t  width;
        uint32_t  height;

        void SetPixel(int x, int y, uint32_t color);
        
        void DrawFilledRectangle(int x, int y, int width, int height, uint32_t color);
        void DrawFilledRoundedRectangle(int x, int y, int width, int height, int radius, uint32_t color);
        void DrawRectangleOutline(int x, int y, int width, int height, uint32_t color);
        
        void DrawFilledCircle(int x, int y, int radius, uint32_t color);
        
        void DrawChar(int x, int y, char c, uint32_t fg, font_t font);
        void DrawString(int x, int y, char* format, uint32_t fg, font_t font);
        void DrawFString(int x, int y, uint32_t fg, font_t font, char* format, ...);

        void DrawAChar(int x, int y, char ch, uint32_t fg, Aaf font);

        void DrawTga(int x, int y, Tga tga);
        void DrawTgaAlpha(int x, int y, Tga tga, uint32_t alpha);

        void DrawBmp(int x, int y, Bmp bmp);
        void DrawBmpAlpha(int x, int y, Bmp bmp, uint32_t alpha);
};