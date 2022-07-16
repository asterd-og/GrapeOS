#include <sys/lib/gfx/aaf.h>
#include <sys/drivers/initrd/ramdisk.h>
#include <sys/debug/dbg.h>
#include <sys/lib/string.h>

void Aaf::load(char* path) {
    uint8_t* data = Tar::fopen(path);
    this->width = data[0];
    this->height = data[1];
    this->spacing = data[2];
    this->data = data;
    Dbg::printf("Font created with width %d and height %d.\n", this->width, this->height);
}