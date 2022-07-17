#include <sys/desktop/elements/dropDown.h>
#include <sys/lib/string.h>
#include <sys/drivers/ps2/mouse.h>

void DropDown::create(int x, int y, int width, int height, uint32_t color, uint32_t colorHovered, uint32_t fg, font_t font, char* firstOpt, Base canvas) {
    this->x = x;
    this->y = y;
    
    this->width = width;
    this->height = height;

    this->color = color;
    this->colorHovered = colorHovered;

    this->fg = fg;
    this->font = font;

    this->optsIdx = 0;
    this->optsSize = 0;
    this->opts[this->optsIdx] = firstOpt;
    this->optsIdx++;
    this->optsSize++;

    this->text = this->opts[0];

    this->type = ElementType::Drop;

    this->clicked = false;
    this->hovering = false;

    this->canvas = canvas;

    this->show = false;

    this->current = this->text;
}

void DropDown::add(char* data) {
    this->opts[this->optsIdx] = data;
    this->optsIdx++;
    this->optsSize++;
}

void DropDown::update() {
    if (Mouse::isWithin(this->x, this->y, this->width, this->height)) {
        memcpy(Mouse::currentCursorData, Mouse::cur_link, 13*11);
        this->hovering = true;
        this->canvas.DrawFilledRectangle(this->x, this->y, this->width, this->height, this->colorHovered);
        if (Mouse::isLeftPressed()) {
            this->clicked = true;
            if (!this->locked) {
                this->locked = true;
                this->show = !this->show;
            }
        } else {
            if (this->clicked) { this->clicked = false; }
            if (this->locked) { this->locked = false; }
        }
    } else {
        if (this->hovering) { this->hovering = false; memcpy(Mouse::currentCursorData, Mouse::cur_normal, 13*11); }
        this->canvas.DrawFilledRectangle(this->x, this->y, this->width, this->height, this->color);
        if (this->clicked) this->clicked = false;
    }
    
    this->canvas.DrawString(this->x + ((this->width/2) - ((strlen(this->current) * font_get_width(this->font)) / 2)),
                            this->y + ((this->height/2) - (font_get_height(this->font)/2)),
                            this->current,
                            this->fg,
                            this->font);
    
    if (this->show) {
        for (int i = 0; i < this->optsSize; i++) {
            if (Mouse::isWithin(this->x, this->y+(i*font_get_height(this->font))+this->height, (this->width < (strlen(this->opts[i])*font_get_width(FONT_SYSTEM_8x8)) ? this->width + strlen(this->opts[i])*font_get_width(FONT_SYSTEM_8x8) : this->width) , font_get_height(this->font))) {
                this->colorC = this->colorHovered;
                if (Mouse::isLeftPressed()) {
                    this->current = this->opts[i];
                    this->show = false;
                }
            } else {
                this->colorC = this->color;
            }
            this->canvas.DrawFilledRectangle(this->x, this->y+(i*font_get_height(this->font))+this->height, (this->width < (strlen(this->opts[i])*font_get_width(FONT_SYSTEM_8x8)) ? this->width + strlen(this->opts[i])*font_get_width(FONT_SYSTEM_8x8) : this->width) , font_get_height(this->font), this->colorC);
            this->canvas.DrawString(this->x, this->y+(i*font_get_height(this->font))+this->height, this->opts[i], this->fg, this->font);
        }
    }
}