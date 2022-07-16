#include <sys/drivers/video/virtualCanvas.h>
#include <sys/drivers/video/canvas.h>
#include <sys/mem/heap.h>
#include <sys/lib/string.h>

void VirtualCanvas::init(int x, int y, uint32_t width, uint32_t height, uint32_t pitch, uint32_t bpp) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->pitch = pitch;
    this->bpp = bpp;
    this->size = this->width * this->height * 4;
    this->buffer = (uint32_t*)Heap::malloc(this->size);
    // memset(this->buffer, 0, this->width*this->height);
}

void VirtualCanvas::Clear(uint32_t color) {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->SetPixel(i, j, color);
        }
    }
}

void VirtualCanvas::Update() {
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            Vbe.SetPixel(i + this->x, j + this->y, this->buffer[j * this->pitch / 4 + i]);
        }
    }
}