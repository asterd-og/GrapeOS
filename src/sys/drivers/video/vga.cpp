// Vga - got some functions from iProgramMC
// https://github.com/iProgramMC/NanoShell-Old

#include <sys/drivers/video/vga.h>
#include <sys/lib/printf.h>
#include <sys/hw/io.h>
#include <sys/debug/dbg.h>

extern "C" void WriteFont8px(unsigned char*);
extern "C" void WriteFont16px(unsigned char*);

unsigned char g_640x480x16[] =
{
/* MISC */
	0xE3,
/* SEQ */
	0x03, 0x01, 0x08, 0x00, 0x06,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0x0B, 0x3E,
	0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xEA, 0x0C, 0xDF, 0x28, 0x00, 0xE7, 0x04, 0xE3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x05, 0x0F,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x01, 0x00, 0x0F, 0x00, 0x00
};

unsigned char g_90x30_text[] =
{
/* MISC */
	0xE7,
/* SEQ */
	0x03, 0x01, 0x03, 0x00, 0x02,
/* CRTC */
	0x6B, 0x59, 0x5A, 0x82, 0x60, 0x8D, 0x0B, 0x3E,
	0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x00,
	0xEA, 0x0C, 0xDF, 0x2D, 0x10, 0xE8, 0x05, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00,
};
unsigned char g_640x480x2[] =
{
/* MISC */
	0xE3,
/* SEQ */
	0x03, 0x01, 0x0F, 0x00, 0x06,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0x0B, 0x3E,
	0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xEA, 0x0C, 0xDF, 0x28, 0x00, 0xE7, 0x04, 0xE3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x0F,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x01, 0x00, 0x0F, 0x00, 0x00
};
unsigned char g_320x200x256[] =
{
/* MISC */
	0x63,
/* SEQ */
	0x03, 0x01, 0x0F, 0x00, 0x0E,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
	0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9C, 0x0E, 0x8F, 0x28,	0x40, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x41, 0x00, 0x0F, 0x00,	0x00
};

unsigned char g_80x25_text[] =
{
/* MISC */
	0x67,
/* SEQ */
	0x03, 0x00, 0x03, 0x00, 0x02,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
	0x00, 0x4F, 0x0D, 0x0E, 0x00, 0x00, 0x00, 0x50,
	0x9C, 0x0E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00
};

unsigned char g_80x50_text[] =
{
/* MISC */
	0x67,
/* SEQ */
	0x03, 0x00, 0x03, 0x00, 0x02,
/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x55, 0x81, 0xBF, 0x1F,
	0x00, 0x47, 0x06, 0x07, 0x00, 0x00, 0x01, 0x40,
	0x9C, 0x8E, 0x8F, 0x28, 0x1F, 0x96, 0xB9, 0xA3,
	0xFF, 
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF, 
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00,
};

unsigned char g_90x60_text[] =
{
/* MISC */
	0xE7,
/* SEQ */
	0x03, 0x01, 0x03, 0x00, 0x02,
/* CRTC */
	0x6B, 0x59, 0x5A, 0x82, 0x60, 0x8D, 0x0B, 0x3E,
	0x00, 0x47, 0x06, 0x07, 0x00, 0x00, 0x00, 0x00,
	0xEA, 0x0C, 0xDF, 0x2D, 0x08, 0xE8, 0x05, 0xA3,
	0xFF,
/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x0E, 0x00,
	0xFF,
/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14, 0x07,
	0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x0C, 0x00, 0x0F, 0x08, 0x00,
};

void Vga::init() {
    this->cursorX = 0;
    this->cursorY = 0;

    this->fg      = VGA_COLOR_WHITE;
    this->bg      = VGA_COLOR_BLACK;

    this->address = (uint16_t*)0xB8000;

    this->clear();
}

void Vga::writeLine(char* fmt, ...) {
    char* buf;
    va_list args;
	va_start(args, fmt);
	vasprintf(buf, fmt, args);
	va_end(args);
    
    while (*buf) {
        this->writeChar(*buf);
        *buf++;
    }

    this->writeChar('\n');
}

void Vga::writeChar(char c) {
    uint8_t  attributeByte = (this->bg << 4) | (this->fg & 0x0F);
    uint16_t attribute = attributeByte << 8;
    uint16_t *location;

    if (c == 0x08 && this->cursorX)
    {
        this->cursorX--;
    }

    else if (c == 0x09)
    {
        this->cursorX = (this->cursorX+8) & ~(8-1);
    }

    else if (c == '\r')
    {
        this->cursorX = 0;
    }

    else if (c == '\n')
    {
        this->cursorX = 0;
        this->cursorY++;
    }

    else if(c >= ' ')
    {
        location = this->address + (this->cursorY*80 + this->cursorX);
        *location = c | attribute;
        this->cursorX++;
    }

    if (this->cursorX >= 80)
    {
        this->cursorX = 0;
        this->cursorY ++;
    }

    this->scroll();
    this->updateCursor();
}

void Vga::write(char* fmt, ...) {
    char* buf;
    va_list args;
	va_start(args, fmt);
	vasprintf(buf, fmt, args);
	va_end(args);
    
    while (*buf) {
        this->writeChar(*buf);
        *buf++;
    }
}

void Vga::clear() {
    uint8_t attributeByte = (this->bg << 4) | (this->fg & 0x0F);
    uint16_t blank = 0x20 | (attributeByte << 8);

    int i;
    for (i = 0; i < 80*25; i++)
    {
        this->address[i] = blank;
    }

    // Move the hardware cursor back to the start.
    this->cursorX = 0;
    this->cursorY = 0;
    this->updateCursor();
}

void Vga::setFg(uint8_t fg) { this->fg = fg; }
void Vga::setBg(uint8_t bg) { this->bg = bg; }

void Vga::setCursor(uint8_t start, uint8_t end) {
    io::outb(0x3D4, 0x0A);
	io::outb(0x3D5, (io::inb(0x3D5) & 0xC0) | start);
 
	io::outb(0x3D4, 0x0B);
	io::outb(0x3D5, (io::inb(0x3D5) & 0xE0) | end);
}

void Vga::switchMode(uint8_t mode) {
    switch(mode)
	{
		case GMode640x480x16:
		#ifdef OptimizeVGA
			this->WriteRegs(g_640x480x16);
			GWidth = VGA_HIRES_MODE_WIDTH;
			GHeight = VGA_HIRES_MODE_HEIGHT;
			// GWritePixel = WritePixelHires;
			GMode = true;
			Optimize = true;
		#else
			this->WriteRegs(g_640x480x16);
			GWidth = VGA_HIRES_MODE_WIDTH;
			GHeight = VGA_HIRES_MODE_HEIGHT;
			// GWritePixel = WritePixel4P;
			GMode = true;
			Optimize = false;
		#endif
			break;
		case GMode640x480x2:
			this->WriteRegs(g_640x480x2);
			GWidth = 640;
			GHeight = 480;
			// GWritePixel = WritePixel1P;
			GMode = true;
			Optimize = false;
			break;
		case GMode320x200x256:
			this->WriteRegs(g_320x200x256);
			GWidth = 320;
			GHeight = 240;
			// GWritePixel = WritePixel8;
			GMode = true;
			Optimize = false;
			break;
		case TMode80x25:
			this->WriteRegs(g_80x25_text);
			VGA_WIDTH = 80;
			VGA_HEIGHT = 25;
			GMode = false;
			WriteFont16px(g_8x16_font);
			Optimize = false;
			break;
		case TMode80x50:
			this->WriteRegs(g_80x50_text);
			VGA_WIDTH = 80;
			VGA_HEIGHT = 50;
			GMode = false;
			WriteFont8px(g_8x8_font);
			Optimize = false;
			break;
		case TMode90x30:
			this->WriteRegs(g_90x30_text);
			VGA_WIDTH = 90;
			VGA_HEIGHT = 30;
			GMode = false;
			WriteFont16px(g_8x16_font);
			Optimize = false;
			break;
		case TMode90x60:
			this->WriteRegs(g_90x60_text);
			VGA_WIDTH = 90;
			VGA_HEIGHT = 60;
			GMode = false;
			WriteFont8px(g_8x8_font);
			Optimize = false;
			break;
	}
}

void Vga::ReadRegs(unsigned char *regs)
{
	unsigned i;

	*regs = io::inb(VGA_MISC_READ);
	regs++;

	for(i = 0; i < VGA_NUM_SEQ_REGS; i++)
	{
		io::outb(VGA_SEQ_INDEX, i);
		*regs = io::inb(VGA_SEQ_DATA);
		regs++;
	}

	for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
	{
		io::outb(VGA_CRTC_INDEX, i);
		*regs = io::inb(VGA_CRTC_DATA);
		regs++;
	}

	for(i = 0; i < VGA_NUM_GC_REGS; i++)
	{
		io::outb(VGA_GC_INDEX, i);
		*regs = io::inb(VGA_GC_DATA);
		regs++;
	}

	for(i = 0; i < VGA_NUM_AC_REGS; i++)
	{
		(void)io::inb(VGA_INSTAT_READ);
		io::outb(VGA_AC_INDEX, i);
		*regs = io::inb(VGA_AC_READ);
		regs++;
	}

	(void)io::inb(VGA_INSTAT_READ);
	io::outb(VGA_AC_INDEX, 0x20);
}

void Vga::WriteRegs(unsigned char *regs)
{
	unsigned i;

	io::outb(VGA_MISC_WRITE, *regs);
	regs++;

	for(i = 0; i < VGA_NUM_SEQ_REGS; i++)
	{
		io::outb(VGA_SEQ_INDEX, i);
		io::outb(VGA_SEQ_DATA, *regs);
		regs++;
	}

	io::outb(VGA_CRTC_INDEX, 0x03);
	io::outb(VGA_CRTC_DATA, io::inb(VGA_CRTC_DATA) | 0x80);
	io::outb(VGA_CRTC_INDEX, 0x11);
	io::outb(VGA_CRTC_DATA, io::inb(VGA_CRTC_DATA) & ~0x80);

	regs[0x03] |= 0x80;
	regs[0x11] &= ~0x80;

	for(i = 0; i < VGA_NUM_CRTC_REGS; i++)
	{
		io::outb(VGA_CRTC_INDEX, i);
		io::outb(VGA_CRTC_DATA, *regs);
		regs++;
	}

	for(i = 0; i < VGA_NUM_GC_REGS; i++)
	{
		io::outb(VGA_GC_INDEX, i);
		io::outb(VGA_GC_DATA, *regs);
		regs++;
	}

	for(i = 0; i < VGA_NUM_AC_REGS; i++)
	{
		(void)io::inb(VGA_INSTAT_READ);
		io::outb(VGA_AC_INDEX, i);
		io::outb(VGA_AC_WRITE, *regs);
		regs++;
	}

	(void)io::inb(VGA_INSTAT_READ);
	io::outb(VGA_AC_INDEX, 0x20);
}

void Vga::updateCursor() {
    uint16_t cursorLocation = this->cursorY * 80 + this->cursorX;
    io::outb(0x3D4, 14);
    io::outb(0x3D5, cursorLocation >> 8);
    io::outb(0x3D4, 15);
    io::outb(0x3D5, cursorLocation);
}

void Vga::scroll()
{
    uint8_t attributeByte = (this->bg << 4) | (this->fg & 0x0F);
    uint16_t blank = 0x20 | (attributeByte << 8);

    if(this->cursorY >= 25)
    {
        int i;
        for (i = 0*80; i < 24*80; i++)
        {
            this->address[i] = this->address[i+80];
        }

        for (i = 24*80; i < 25*80; i++)
        {
            this->address[i] = blank;
        }

        this->cursorY = 24;
    }
}