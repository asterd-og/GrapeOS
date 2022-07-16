#pragma once

#include <stdint.h>
#include <stddef.h>

#define USTAR_MAGIC "ustar"

#define OLDGNU_MAGIC "ustar  "  /* 7 chars and a null */
#include <stdbool.h>

namespace Tar {
	enum class ustar_typeflag : char
	{
		file = '0',
		hardlink = '1',
		symlink = '2',
		char_device = '3',
		block_device = '4',
		directory = '5',
		fifo = '6'
	};
	struct __attribute__((packed)) ustar_entry
	{
		char					 name[100];
		char					 mode[8];
		char					 uid[8];
		char					 gid[8];
		char					 size[12];
		char					 last_modified[12];
		char					 checksum[8];
		ustar_typeflag			 typeflag;
		char					 linkname[100];
		char					 magic[6];
		char					 version[2];
		char					 uname[32];
		char					 gname[32];
		char					 devmajor[8];
		char					 devminor[8];
		char					 prefix[155];
		char					 pad[12];
	};

	typedef ustar_entry *TAR_DIR;
	typedef ustar_entry *TAR_FILE;

	size_t calc_size();
	uint8_t *fopen(const char *name);
	void list_all();
	size_t ftell(const char *path);
	uint32_t Size();
	void SetRamdisk(uint8_t* addr);
}