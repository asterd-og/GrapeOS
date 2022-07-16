#include <sys/drivers/ps2/kb.h>
#include <sys/hw/io.h>
#include <sys/tables/idt/irq.h>
#include <sys/software/shell.h>

namespace Kb {
	uint8_t shift = 0;
	uint8_t caps = 0;

	char current_char;
	int32_t current_keycode;

	bool pressed = false;

	void handler(registers_t *r) {
		uint8_t status;
		signed char keycode;
		//write interrupt end
		io::outb(0x20, 0x20);

		status = io::inb(0x64);
		if(status & 1){
			keycode = io::inb(0x60);
			handle_key(keycode);
		} else {
			current_char = 0;
			current_keycode = 0;
		}
	}

	void handle_key(int32_t keycode) {
	    switch(keycode) {
			case SHIFT:
				shift = 1;
				break;
			case SHIFT_RELEASE:
				shift = 0;
				break;
			case CAPSLOCK:
				if(caps > 0){
					caps = 0;
				} else {
					caps = 1;
				}
				break;
			default:
				if(keycode < 0) return;
				char ch;
				if(shift || caps) {
					ch = keymap_upper[keycode];
				} else {
					ch = keymap_lower[keycode];
				}
				current_char=ch;
				current_keycode=keycode;
	            // Shell::handleKey(keycode, ch);
				break;
		}
	}

	char getChar() {
		char ch=current_char;
		current_char=0;
		return ch;
	}

	int32_t getKeycode() {
		int32_t keycode=current_keycode;
		current_keycode=0;
		return keycode;
	}

	bool tryReadKey() {
		uint8_t status;
		signed char keycode;
		//write interrupt end
		io::outb(0x20, 0x20);

		status = io::inb(0x64);
		if(status & 1){
			keycode = io::inb(0x60);
			if (keycode >= 0x90) {
				return false;
			} else {
				return true;
			}
		}
	}

	void install() {
		Irq::install_handler(1, handler);
	}
}