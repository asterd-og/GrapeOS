#include <sys/debug/dbg.h>
#include <sys/lib/printf.h>
#include <sys/lib/string.h>
#include <sys/hw/io.h>
#include <stdarg.h>

namespace Dbg {
	void setport(int port)
	{
	}

	void enable() {
		io::outb(PORT_A + 1, 0x00);
		io::outb(PORT_A + 3, 0x80); /* Enable divisor mode */
		io::outb(PORT_A + 0, 0x03); /* Div Low:  03 Set the port to 38400 baud */
		io::outb(PORT_A + 1, 0x00); /* Div High: 00 */
		io::outb(PORT_A + 3, 0x03); /* 8 bits, no parity, one stop bit */
		io::outb(PORT_A + 2, 0xC7);
		io::outb(PORT_A + 4, 0x0B);
	}

	int rcvd() {
		return io::inb(PORT_A + 5) & 1;
	}

	char recv() {
		while (rcvd() == 0) ;
		return io::inb(PORT_A);
	}

	int recv_string(char* buf, int size) {
		if(size == 0)
			return 0;
		int pos = 0;
		while(1) {
			char c = recv();
			buf[pos] = c;
			pos++;
			if(c == 0 || c == '\n' || pos >= size)
				return pos;
		}
	}

	char recv_async() {
		return io::inb(PORT_A);
	}

	int transmit_empty() {
		return io::inb(PORT_A + 5) & 0x20;
	}

	void send(char out) {
		while (transmit_empty() == 0);
		io::outb(PORT_A, out);
	}

	void send_string( char * out) {
	    while (*out) {
	        send(*out);
	        *out++;
	    }
	}

	int printf(const char* fmt, ...) {
		char* buf;
		va_list args;
		va_start(args, fmt);
		int out = vasprintf(buf, fmt, args);
		va_end(args);
		send_string(buf);
		return out;
	}
}