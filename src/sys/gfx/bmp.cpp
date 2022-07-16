#include <sys/gfx/bmp.h>
#include <sys/lib/math.h>
#include <sys/lib/string.h>
#include <sys/mem/heap.h>
#include <sys/drivers/initrd/ramdisk.h>

// constructor - load from disk
void Bmp::load(char* name)
{
    uint8_t* data = Tar::fopen(name);
    uint8_t size = Tar::ftell(name);
    bmp_fileheader_t* h = (bmp_fileheader_t*)data;
    uint32_t offset = h->bfOffBits;
    bmp_infoheader_t* info = (bmp_infoheader_t*)(data + sizeof(bmp_fileheader_t));
    
    this->width = info->biWidth;
    this->height = info->biHeight;
    this->imageData = (uint8_t*)((uint32_t)data + offset);
    this->buffer = (uint8_t*)data;
    this->totalSize = size;
    this->depth = (COLOR_DEPTH)info->biBitCount;
    if (this->width == 0 || this->height == 0 || this->depth == 0) { return; }
    uint32_t* new_data = (uint32_t*)Heap::malloc(this->width * this->height * 4);
    memset(new_data, 0, this->width * this->height * 4);
    for (int32_t yy = this->height - 1; yy >= 0; yy--)
    {
        for (int32_t xx = 0; xx < this->width; xx++)
        {
            if (this->depth == COLOR_DEPTH_24)
            {
                uint32_t offset = (3 * (xx + (yy * this->width)));
                uint32_t color = RGBToPackedValue(this->imageData[offset + 2], this->imageData[offset + 1], this->imageData[offset]);
                uint32_t output_offset = xx + ((this->height - yy - 1) * this->width);
                new_data[output_offset] = color;
            }
            else if (this->depth == COLOR_DEPTH_32)
            {
                uint32_t offset = (4 * (xx + (yy * this->width)));
                uint32_t color = RGBToPackedValue(this->imageData[offset + 2], this->imageData[offset + 1], this->imageData[offset]);
                uint32_t output_offset = xx + ((this->height - yy - 1) * this->width);
                new_data[output_offset] = color;
            }
            else if(this->depth == COLOR_DEPTH_8)
            {
                uint32_t offset = (1 * (xx + (yy * this->width)));
                uint32_t color = RGBToPackedValue(this->imageData[offset], this->imageData[offset], this->imageData[offset]);
                uint32_t output_offset = xx + ((this->height - yy - 1) * this->width);
                new_data[output_offset] = color;
            }
            else if(this->depth == COLOR_DEPTH_4)
            {
                uint32_t offset = (xx + (yy * this->width));
                uint32_t color = RGBToPackedValue(this->imageData[offset], this->imageData[offset], this->imageData[offset]);
                uint32_t output_offset = xx + ((this->height - yy - 1) * this->width);
                new_data[output_offset] = color;
            }
        }
    }
    this->imageData = (uint8_t*)new_data;
    Heap::free(data);
}

void Bmp::resize(int32_t w, int32_t h)
{
    uint32_t* temp = (uint32_t*)Heap::malloc(w * h * 4);
    memset(temp, 0, w * h * 4);
    double x_ratio = (double)this->width / (double)w;
    double y_ratio = (double)this->height / (double)h;
    int px, py;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            px = floor(j * x_ratio);
            py = floor(i * y_ratio);
            temp[(i * w) + j] = ((uint32_t*)this->imageData)[(int)((py * this->width) + px)];
        }
    }
    Heap::free(this->imageData);
    this->imageData = (uint8_t*)temp;
    
    this->width = w;
    this->height = h;
}