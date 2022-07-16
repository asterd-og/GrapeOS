CFILES=$(wildcard src/boot/*.c)

CPPFILES=$(wildcard src/kernel/*.cpp	   	\
		   src/sys/drivers/video/*.cpp		\
		   src/sys/drivers/initrd/*.cpp		\
		   src/sys/drivers/ps2/*.cpp		\
		   src/sys/tables/gdt/*.cpp			\
		   src/sys/tables/idt/*.cpp			\
		   src/sys/software/*.cpp			\
		   src/sys/lib/*.cpp				\
		   src/sys/lib/gfx/*.cpp			\
		   src/sys/hw/*.cpp					\
		   src/sys/mem/*.cpp				\
		   src/sys/gfx/*.cpp				\
		   src/sys/debug/*.cpp				\
		   src/sys/desktop/*.cpp			\
		   src/sys/lib/imgs/*.cpp			\
		   src/sys/desktop/elements/*.cpp	\
		   src/sys/usermode/*.cpp			\
)

ASMFILES=$(wildcard src/sys/asm/*.asm)
SFILES=$(wildcard src/sys/asm/*.s)

KERNEL=conf/grub/boot/kernel.bin
ISO=GrapeOS.iso

CC=i686-elf-gcc
CXX=i686-elf-g++

CXXFLAGS=-Isrc/        					 \
		 -fno-use-cxa-atexit 			 \
		 -ffreestanding 				 \
		 -O2 							 \
		 -Wall 							 \
		 -Wextra 						 \
		 -fno-exceptions 				 \
		 -fno-rtti 						 \
		 -Wno-write-strings 			 \
		 -Wno-unused-variable 			 \
		 -w 							 \
		 -Wno-narrowing 				 \
		 -Wno-sign-compare 				 \
		 -Wno-type-limits 				 \
		 -Wno-unused-parameter 			 \
		 -Wno-missing-field-initializers \
		 -fpermissive					 \
		 -DVBE_MODE	

LDINTERNALFLAGS := \
	-m elf_i386    \
	-Tconf/linker.ld\

override OBJ := $(ASMFILES:.asm=_asm.a)
override OBJ += $(SFILES:.s=_s.o)
override OBJ += $(CFILES:.c=.o)
override OBJ += $(CPPFILES:.cpp=.o)

all: $(KERNEL) genfs geniso run clean

# Link rules for the final kernel executable.
$(KERNEL): $(OBJ)
	i686-elf-ld $(LDINTERNALFLAGS) -o $@ $(OBJ)

genfs:
	tar czf  conf/grub/ramdisk/initrd.img -C conf/ramdisk/ ./ --format=ustar

geniso:
	grub-mkrescue -o $(ISO) conf/grub/

run:
	qemu-system-i386 -m 2G -serial stdio -cdrom $(ISO) -no-reboot -no-shutdown

%.o: %.c
	$(CC) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%_asm.a: %.asm
	nasm -f elf $< -o $@

%_s.o: %.s
	as --32 -c $< -o $@

clean:
	rm -fr $(KERNEL) $(OBJ)