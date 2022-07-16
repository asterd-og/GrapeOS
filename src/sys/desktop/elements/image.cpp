#include <sys/desktop/elements/image.h>
#include <sys/lib/string.h>
#include <sys/drivers/ps2/mouse.h>

void Image::create(int x, int y, Bmp img, Base canvas) {
    this->x = x;
    this->y = y;
    
    this->image = img;

    this->type = ElementType::Img;

    this->canvas = canvas;
}

void Image::update() {
    this->canvas.DrawBmp(this->x, this->y, this->image);
}