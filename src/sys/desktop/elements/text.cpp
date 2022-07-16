#include <sys/desktop/elements/text.h>
#include <sys/lib/string.h>
#include <sys/drivers/ps2/mouse.h>

void Text::create(int x, int y, uint32_t color, font_t font, char* text, Base canvas) {
    this->x = x;
    this->y = y;
    
    this->fg = color;
    this->font = font;
    
    this->type = ElementType::Txt;

    this->text = text;
    this->canvas = canvas;
}

void Text::update() {
    this->canvas.DrawString(this->x, this->y, this->text, this->fg, this->font);
}