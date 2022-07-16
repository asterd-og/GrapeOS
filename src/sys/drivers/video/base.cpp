#include <sys/drivers/video/base.h>
#include <sys/lib/string.h>

void Base::SetPixel(int x, int y, uint32_t color) {
    if (x<0||y<0||x>this->width||y>this->height) return;
    this->buffer[y * this->pitch / 4 + x]=color;
}

void Base::DrawFilledRectangle(int x, int y, int width, int height, uint32_t color) {
    for (int i=x; i<x+width; i++) {
        for (int j=y; j<y+height; j++) {
            this->SetPixel(i, j, color);
        }
    }
}

void Base::DrawFilledRoundedRectangle(int x, int y, int width, int height, int radius, uint32_t color) {
    this->DrawFilledRectangle(x + radius, y, width - radius * 2, height, color);
    this->DrawFilledRectangle(x, y + radius, width, height - radius * 2, color);

    this->DrawFilledCircle(x + radius, y + radius, radius, color);
    this->DrawFilledCircle(x + width - radius - 1, y + radius, radius, color);

    this->DrawFilledCircle(x + radius, y + height - radius - 1, radius, color);
    this->DrawFilledCircle(x + width - radius - 1, y + height - radius - 1, radius, color);
}

void Base::DrawRectangleOutline(int x, int y, int width, int height, uint32_t color) {
    for (int i=x;i<x+width+1;i++) {
        this->SetPixel(i, y, color); //top line
        this->SetPixel(i, y+height, color); //down line
    }
    for (int i=y;i<y+height;i++) {
        this->SetPixel(x, i, color); //left line
        this->SetPixel(x+width, i, color); //right line
    }
}

void Base::DrawFilledCircle(int x, int y, int radius, uint32_t color) {
    int r2 = radius * radius;
    int area = r2 << 2;
    int rr = radius << 1;

    for (int i = 0; i < area; i++)
    {
        int tx = (i % rr) - radius;
        int ty = (i / rr) - radius;

        if (tx * tx + ty * ty <= r2)
            this->SetPixel(x + tx, y + ty, color);
    }
}

void Base::DrawChar(int x, int y, char c, uint32_t fg, font_t font) {
    if (c == 0) { return; }
    uint32_t p = font.height * c;
    for (size_t cy = 0; cy < font.height; cy++)
    {
        for (size_t cx = 0; cx < font.width; cx++)
        {
            if (bit_address_from_byte(font.data[p + cy], cx + 1))
            { this->SetPixel(x + (font.width - cx), y + cy, fg); }
        }
    }
}

void Base::DrawString(int x, int y, char* format, uint32_t fg, font_t font) {
    uint32_t len = strlen(format);
    uint32_t xx = x, yy = y;
    for (uint32_t i = 0; i < len; i++)
    {
        if (format[i] == 0) { break; }
        if (format[i] == '\n') { xx = x; yy += font_get_height(font); continue; }
        if (isprint(format[i])) { Base::DrawChar(xx, yy, format[i], fg, font); xx += font_get_width(font); }
    }
}

void Base::DrawFString(int x, int y, uint32_t fg, font_t font, char* fmt, ...) {
    char* buf;
	va_list args;
	va_start(args, fmt);
	vasprintf(buf, fmt, args);
	va_end(args);
    Base::DrawString(x, y, buf, fg, font);
}

void Base::DrawAChar(int x, int y, char ch, uint32_t fg, Aaf font) {
    int offset = ch;
    if (ch != 'A') {
        offset += font.height;
    }
    for (size_t yy = 0; yy < font.height; yy++) {
        for (size_t xx = 0; xx < font.width; xx++) {
            if (font.data[offset + (xx + (yy * font.width))] != 0) this->SetPixel(x+xx, y+yy, fg);
        }
    }
}

void Base::DrawTga(int x, int y, Tga tga) {
    int w=tga.width;
    int h=tga.height;

    for (size_t yy = 0; yy < h; yy++)
    {
        for (size_t xx = 0; xx < w; xx++)
        {
            size_t color = tga.data[2+(xx + (yy * w))];
            this->SetPixel(x + xx, y + yy, color);
        }
    }
}

void Base::DrawTgaAlpha(int x, int y, Tga tga, uint32_t alpha) {
    int w=tga.width;
    int h=tga.height;

    for (size_t yy = 0; yy < h; yy++)
    {
        for (size_t xx = 0; xx < w; xx++)
        {
            size_t color = tga.data[2+(xx + (yy * w))];
            if (color!=alpha) this->SetPixel(x + xx, y + yy, color);
        }
    }
}

void Base::DrawBmp(int x, int y, Bmp bmp) {
    int w=bmp.width;
    int h=bmp.height;
    size_t* data = (size_t*)bmp.imageData;

    for (size_t yy = 0; yy < h; yy++)
    {
        for (size_t xx = 0; xx < w; xx++)
        {
            size_t color = data[(xx + (yy * w))];
            this->SetPixel(x + xx, y + yy, color);
        }
    }
}

void Base::DrawBmpAlpha(int x, int y, Bmp bmp, uint32_t alpha) {
    int w=bmp.width;
    int h=bmp.height;
    size_t* data = (size_t*)bmp.imageData;

    for (size_t yy = 0; yy < h; yy++)
    {
        for (size_t xx = 0; xx < w; xx++)
        {
            size_t color = data[(xx + (yy * w))];
            if ((uint32_t)color!=alpha) { this->SetPixel(x + xx, y + yy, color); }
        }
    }
}