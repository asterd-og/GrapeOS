#include <kernel/multiboot.h>

namespace Multiboot {
    multiboot_t* mboot;

    void read(void* ptr) {
        mboot=(multiboot_t*)ptr;
    }

    void *get_module(size_t indx)
    {
        if (indx > get()->mods_count)
        {
            return NULL;
        }
        uintptr_t *mods = (uintptr_t*)get()->mods_addr;
        return (void*)mods[indx];
    }

    multiboot_t* get() {
        return mboot;
    }
}