#include <sys/desktop/elements/button.h>
#include <sys/lib/string.h>
#include <sys/drivers/ps2/mouse.h>

void Button::create(int x, int y, int width, int height, uint32_t color, uint32_t colorHovered, uint32_t fg, font_t font, char* text, Base canvas) {
    this->x = x;
    this->y = y;

    this->width = width;
    this->height = height;

    this->color = color;
    this->fg = fg;
    this->colorHovered = colorHovered;

    this->text = text;

    this->font = font;

    this->type = ElementType::Btn;

    this->clicked = false;
    this->hovering = false;

    this->canvas = canvas;
}

void Button::update() {
    if (Mouse::isWithin(this->x, this->y, this->width, this->height)) {
        memcpy(Mouse::currentCursorData, Mouse::cur_link, 13*11);
        this->hovering = true;
        this->canvas.DrawFilledRectangle(this->x, this->y, this->width, this->height, this->colorHovered);
        if (Mouse::isLeftPressed()) {
            this->clicked = true;
        } else {
            if (this->clicked) this->clicked = false;
        }
    } else {
        if (this->hovering) { this->hovering = false; memcpy(Mouse::currentCursorData, Mouse::cur_normal, 13*11); }
        this->canvas.DrawFilledRectangle(this->x, this->y, this->width, this->height, this->color);
        if (this->clicked) this->clicked = false;
    }
    
    this->canvas.DrawString(this->x + ((this->width/2) - ((strlen(this->text) * font_get_width(this->font)) / 2)),
                            this->y + ((this->height/2) - (font_get_height(this->font)/2)),
                            this->text,
                            this->fg,
                            this->font);
}