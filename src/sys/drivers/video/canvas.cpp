#include <sys/drivers/video/canvas.h>
#include <sys/mem/heap.h>
#include <sys/debug/dbg.h>
#include <sys/mem/paging.h>
#include <sys/lib/string.h>
#include <sys/lib/math.h>

void Canvas::Init(int width, int height, uint32_t pitch, uint32_t bpp, uint32_t* FBAddr) {
    Paging::v2p((uint32_t)FBAddr, (uint32_t)FBAddr);
    this->width=width;
    this->height=height;
    this->pitch=pitch;
    this->bpp=bpp;
    this->FBAddr=FBAddr;
    this->size=this->width*this->height*4;
    this->buffer=(uint32_t*)Heap::malloc(this->size);
}

void Canvas::Clear(uint32_t color) {
    for (int i=0;i<this->width*this->height;i++) {
        this->buffer[i]=color;
    }
}

void Canvas::Update() {
    for (int i=0;i<this->width*this->height;i++) {
        this->FBAddr[i]=this->buffer[i];
    }
}