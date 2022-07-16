#pragma once

// Copyright (C) 2022  Astrido

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define K 1024
#define M (1024*K)
#define G (1024*M)

#define ALLOC_MAGIC 0xDEADBEEF

namespace Heap {
    struct alloc {
        size_t        size;
        uint32_t      magic;
        bool          paligned;
    };

    typedef struct alloc alloc;

    void   init(uint32_t* saddr);
    void*  kmalloc(size_t size);
    void*  krealloc(void* ptr, size_t size);
    void*  kcalloc(size_t num, size_t size);
    size_t kallocsize(void* ptr);
    void   kfree(void* ptr);

    void*  malloc(size_t size);
    void*  realloc(void* ptr, size_t size);
    void*  calloc(size_t num, size_t size);
    size_t allocsize(void* ptr);
    void   free(void* ptr);

    uint32_t mem_get_free_ram();
    uint32_t mem_get_used_ram();
    uint32_t mem_get_total_ram();
}