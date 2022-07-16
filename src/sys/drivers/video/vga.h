#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <sys/lib/string.h>
#include <sys/drivers/video/vga_fonts.h>

typedef enum {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
} vga_color;

#define	VGA_AC_INDEX		0x3C0
#define	VGA_AC_WRITE		0x3C0
#define	VGA_AC_READ		    0x3C1
#define	VGA_MISC_WRITE		0x3C2
#define VGA_SEQ_INDEX		0x3C4
#define VGA_SEQ_DATA		0x3C5
#define	VGA_DAC_READ_INDEX	0x3C7
#define	VGA_DAC_WRITE_INDEX	0x3C8
#define	VGA_DAC_DATA		0x3C9
#define	VGA_MISC_READ		0x3CC
#define VGA_GC_INDEX 		0x3CE
#define VGA_GC_DATA 		0x3CF
/*			COLOR emulation		MONO emulation */
#define VGA_CRTC_INDEX		0x3D4		/* 0x3B4 */
#define VGA_CRTC_DATA		0x3D5		/* 0x3B5 */
#define	VGA_INSTAT_READ		0x3DA

#define	VGA_NUM_SEQ_REGS	5
#define	VGA_NUM_CRTC_REGS	25
#define	VGA_NUM_GC_REGS		9
#define	VGA_NUM_AC_REGS		21
#define	VGA_NUM_REGS		(1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + \
				VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)
				
#define MK_FP(S, O) ((S << 4) + O)
#define FP_SEG(F) (F >> 16)
#define FP_OFF(F) (F & 0xffff)
			
#define	peekb(S,O)		*(unsigned char *)MK_FP(S, O)
#define	pokeb(S,O,V)		*(unsigned char *)MK_FP(S, O) = (V)
#define	pokew(S,O,V)		*(unsigned short *)MK_FP(S, O) = (V)
#define ppokeb(A,V)			*(unsigned char*)(A) = (V)
#define ppeekb(A)			*(unsigned char*)(A)
#define	_vmemwr(DS,DO,S,N)	movedata(FP_SEG(S), FP_OFF(S), DS, DO, N)
#define	vmemwr(a,b,c)	memcpy((void*)(a),b,c);

#define GMode640x480x16 0x12
#define GMode320x200x256 0x13
#define GMode640x480x2 0x14
#define TMode80x25 0xea
#define TMode80x50 0xc3
#define TMode90x30 0xfa
#define TMode90x60 0xce
#define VGA_HIRES_MODE_WIDTH 640
#define VGA_HIRES_MODE_HEIGHT 480
#define VGA_HIRES_MODE_PIXELSPERBYTE 2

class Vga {
    private:
        uint16_t* address;

        static void (*GWritePixel)(unsigned x, unsigned y, unsigned c);

        void ReadRegs(unsigned char *regs);
        void WriteRegs(unsigned char *regs);

        void updateCursor();

        void scroll();

        bool GMode = false;
        uint8_t HiresFrameBuffer[153600];
        uint16_t GWidth, GHeight;
        uint16_t VGA_WIDTH = 80;
        uint16_t VGA_HEIGHT = 25;
        bool Optimize = false;
    
    public:
        int cursorX;
        int cursorY;

        uint8_t fg;
        uint8_t bg;

        void init();

        void writeLine(char* str, ...);
        void writeChar(char c);
        void write(char* str, ...);

        void clear();

        void setFg(uint8_t fg);
        void setBg(uint8_t bg);

        void setCursor(uint8_t start, uint8_t end);

        void switchMode(uint8_t mode);
};

extern Vga Console;