#pragma once

#include <stdint.h>
#include <stddef.h>

typedef enum
{
    COLOR_DEPTH_4   = 4,
    COLOR_DEPTH_8   = 8,
    COLOR_DEPTH_16  = 16,
    COLOR_DEPTH_24  = 24,
    COLOR_DEPTH_32  = 32,
} COLOR_DEPTH;

static inline  uint32_t RGBToPackedValue(uint8_t r, uint8_t g, uint8_t b)
{
    if (r == 0 && g == 0 && b == 0) { return 0xFF000000; }
    return (uint32_t)((0xFF << 24) | (r << 16) | (g << 8) | b);
}

typedef struct tagBITMAPFILEHEADER 
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
}__attribute__((packed)) bmp_fileheader_t;

typedef struct tagBITMAPINFOHEADER 
{
    uint32_t    biSize;
    long        biWidth;
    long        biHeight;
    uint16_t    biPlanes;
    uint16_t    biBitCount;
    uint32_t    biCompression;
    uint32_t    biSizeImage;
    long        biXPelsPerMeter;
    long        biYPelsPerMeter;
    uint32_t    biClrUsed;
    uint32_t    biClrImportant;
}bmp_infoheader_t;

class Bmp {
    public:
        int width, height;
        COLOR_DEPTH depth;
        uint8_t* imageData;
        uint8_t* buffer;
        uint32_t totalSize;

        void load(char* name);
        void resize(int32_t width, int32_t height);
};