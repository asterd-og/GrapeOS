#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct
{
    int X;
    int Y;
    uint32_t Width;
    uint32_t Height;
} __attribute__((packed)) bounds_t;

typedef struct
{
    int32_t X;
    int32_t Y;
} __attribute__((packed)) point_t;