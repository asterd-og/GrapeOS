// Heap - original file by Astrido
// https://github.com/asterd-og/GrapeOS

#include <sys/mem/heap.h>
#include <sys/mem/paging.h>
#include <sys/lib/string.h>
#include <sys/debug/dbg.h>
#include <kernel/multiboot.h>

namespace Heap {
    uint32_t usable_mem;
    uint32_t total_mem;
    uint32_t used_mem;
    uint32_t total=0;
    uint32_t heap_start=0;
    uint32_t heap_end=0;
    uint32_t last_address=0;

    //UTILS

    size_t align(size_t size) {
    	size_t aligned_size = size;
        if(size % 4 != 0)
        {
            aligned_size += 4 - (size % 4);
        }
        return aligned_size;
    }

    uint32_t get_memory_map() {
        multiboot_info_t* info = Multiboot::get();
        if(info->flags & MULTIBOOT_INFO_MEMORY)  {
            multiboot_memory_map_t* mmap = (multiboot_memory_map_t*)info->mmap_addr;
            multiboot_memory_map_t* mmap_end = (multiboot_memory_map_t*)(info->mmap_addr + info->mmap_length);
            while(mmap < mmap_end) {
                if(mmap->type == 1) {
                    total += mmap->len;
                }
                mmap = (multiboot_memory_map_t*)((uint32_t)mmap + mmap->size + sizeof(mmap->size));
            }
            return total;
        }
    }

    //HEAP

    void init(uint32_t* saddr) {
        total=get_memory_map();
        usable_mem=total;
        total_mem=usable_mem;
        heap_start=align((size_t)(saddr+(1*M)));
        heap_end=heap_start+usable_mem;
        last_address=heap_start;
        Dbg::printf("Heap starts at 0x%x. Usable memory: %d mb.\n", heap_start, usable_mem/1024/1024);
    }

    void* kmalloc(size_t size) {
        if (size>usable_mem) { Dbg::printf("KMalloc Error: Size is greater than the usable memory!\n"); return NULL; }
        alloc* ac=(alloc*)last_address;
        if (ac->magic==ALLOC_MAGIC) {
            while (ac->magic==ALLOC_MAGIC) {
                if (last_address>=heap_end) {
                    Dbg::printf("KMalloc Error: Could not find an empty address!\n");
                    return NULL;
                }
                last_address+=ac->size;
                ac=(alloc*)last_address;
            }
        }
        ac->magic=ALLOC_MAGIC;
        ac->size=size;
        last_address+=(size+sizeof(alloc*));
        usable_mem-=size;
        used_mem+=size;
        Dbg::printf("KMalloc Success: Allocated %d bytes at 0x%x. Infos: Addrend: 0x%x Magic: 0x%x Size: %d.\n",
                    size,
                    (last_address-size),
                    (last_address-size)+ac->size,
                    ac->magic,
                    ac->size);
        return (void*)(last_address-size);
    }

    void* krealloc(void* ptr, size_t size)
    {
        void* newptr = kmalloc(size);
        memcpy(newptr, ptr, size);
        kfree(ptr);
        return newptr;
    }

    void* kcalloc(size_t num, size_t size) {
        void * ptr = kmalloc(num * size);
        memset(ptr, 0, num*size);
        return ptr;
    }

    size_t kallocsize(void* ptr) {
        if (!ptr) return;
        return ((alloc*)(((uint32_t)ptr)-sizeof(alloc*)))->size;
        // if (((alloc*)ptr-sizeof(alloc*))->magic==ALLOC_MAGIC) { return ((alloc*)(((uint32_t)ptr)-sizeof(alloc*)))->size; }
        // else { Dbg::printf("KAlloc Error: 0x%x wasnt allocated.\n"); return NULL; }
    }

    void kfree(void* ptr) {
        if (ptr==NULL) { Dbg::printf("KFree Error: Freeing object is null.\n"); return; }
        alloc* ac=(alloc*)(((uint32_t)ptr)-sizeof(alloc*));

        size_t size=ac->size;
        uint32_t ptraddr=(uint32_t)ptr;

        ac->magic=0;
        ac->size=0;

        ptr=NULL;

        usable_mem+=size;
        used_mem-=size;
        last_address-=(size-sizeof(alloc*));

        Dbg::printf("KFree Success: Freed %d bytes at 0x%x.\n", size, ptraddr);
        size=NULL;
        ptraddr=NULL;
        return;
    }

    //WRAPPERS

    size_t allocsize(void* ptr) {
        return kallocsize(ptr);
    }

    void*malloc(size_t size){
        return kmalloc(size);
    }

    void*realloc(void* ptr,size_t size){
        return krealloc(ptr,size);
    }

    void*calloc(size_t num,size_t size){
        return kcalloc(num,size);
    }

    void free(void*ptr){
        return kfree(ptr);
    }

    uint32_t mem_get_free_ram() {
        return usable_mem;
    }

    uint32_t mem_get_used_ram() {
        return used_mem;
    }

    uint32_t mem_get_total_ram() {
        return total_mem;
    }
}

void *operator new(size_t size)
{
    return Heap::malloc(size);
}

void *operator new[](size_t size)
{
    return Heap::malloc(size);
}

void operator delete(void *ptr)
{
    Heap::free(ptr);
}

void operator delete[](void *ptr)
{
    Heap::free(ptr);
}