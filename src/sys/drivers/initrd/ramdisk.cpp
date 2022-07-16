#include <sys/drivers/initrd/ramdisk.h>
#include <sys/lib/string.h>
#include <sys/mem/heap.h>
#include <sys/debug/dbg.h>

namespace Tar {
    uint8_t *ramdisk;
	size_t ramdisk_size;

	bool root_validate()
	{
		TAR_DIR root = ((TAR_DIR)ramdisk)+0;
		return strcmp(root->magic, USTAR_MAGIC) == 0;
	}
	void SetRamdisk(uint8_t* addr)
	{
	    ramdisk = addr;
	}
	size_t calc_size()
	{
		uintptr_t entry = (uintptr_t)ramdisk;
		size_t size = 0;

		if (!root_validate()) return 0;

		for (TAR_DIR dir = (TAR_DIR)entry; strcmp(dir->magic, USTAR_MAGIC) == 0; dir = (TAR_DIR)entry)
		{
			size_t sz = stroct(dir->size);
			entry += (((sz + 511) / 512) + 1) * 512;
			size += stroct(dir->size) + sizeof(ustar_entry);
		}

		return ramdisk_size = size;
	}

	uint8_t *fopen(const char *name)
	{
		uintptr_t entry = (uintptr_t)ramdisk;

		if (!root_validate()) return 0;

		for (TAR_DIR dir = (TAR_DIR)entry; strcmp(dir->magic, USTAR_MAGIC) == 0; dir = (TAR_DIR)entry)
		{

			if (dir->typeflag == ustar_typeflag::directory)
			{
				entry += sizeof(ustar_entry);
				continue;
			}
			size_t sz = stroct(dir->size);
			if (strcmp(dir->name, (char*)name) == 0)
			{
				return (uint8_t*)entry + 512;
			}

			entry += (((sz + 511) / 512) + 1) * 512;

		}

		return 0;
	}

	void list_all()
	{
		uintptr_t entry = (uintptr_t)ramdisk;

		if (!root_validate()) return;

		for (TAR_DIR dir = (TAR_DIR)entry; strcmp(dir->magic, USTAR_MAGIC) == 0; dir = (TAR_DIR)entry)
		{
			size_t sz = stroct(dir->size);
			Dbg::printf("%s\n", dir->name);
			entry += (((sz + 511) / 512) + 1) * 512;

		}
	}

	size_t ftell(const char *path)
	{
		uintptr_t entry = (uintptr_t)ramdisk;
		size_t size = 0;

		if (!root_validate()) return 0;

		for (TAR_DIR dir = (TAR_DIR)entry; strcmp(dir->magic, USTAR_MAGIC) == 0; dir = (TAR_DIR)entry)
		{
			size_t sz = stroct(dir->size);

			if (strcmp(dir->name, (char*)path) == 0)
			{
				return sz;
			}

			entry += (((sz + 511) / 512) + 1) * 512;
			size += stroct(dir->size);
		}

		return 0;
	}
}