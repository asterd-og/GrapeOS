#include <sys/lib/printf.h>
#include <sys/lib/string.h>

int is_format_letter(char c) {
    return c == 'c' ||  c == 'd' || c == 'i' ||c == 'e' ||c == 'E' ||c == 'f' ||c == 'g' ||c == 'G' ||c == 'o' ||c == 's' || c == 'u' || c == 'x' || c == 'X' || c == 'p' || c == 'n';
}

void vsprintf(char * str, void (*putchar)(char), const char * format, va_list arg) {
    uint32_t pos = 0;
    vsprintf_helper(str, putchar, format, &pos, arg);
}

static void print_dec(unsigned int value, unsigned int width, char * buf, int * ptr ) {
	unsigned int n_width = 1;
	unsigned int i = 9;
	while (value > i && i < UINT32_MAX) {
		n_width += 1;
		i *= 10;
		i += 9;
	}

	int printed = 0;
	while (n_width + printed < width) {
		buf[*ptr] = '0';
		*ptr += 1;
		printed += 1;
	}

	i = n_width;
	while (i > 0) {
		unsigned int n = value / 10;
		int r = value % 10;
		buf[*ptr + i - 1] = r + '0';
		i--;
		value = n;
	}
	*ptr += n_width;
}

static void print_hex(unsigned int value, unsigned int width, char * buf, int * ptr) {
	int i = width;

	if (i == 0) i = 8;

	unsigned int n_width = 1;
	unsigned int j = 0x0F;
	while (value > j && j < UINT32_MAX) {
		n_width += 1;
		j *= 0x10;
		j += 0x0F;
	}

	while (i > (int)n_width) {
		buf[*ptr] = '0';
		*ptr += 1;
		i--;
	}

	i = (int)n_width;
	while (i-- > 0) {
		buf[*ptr] = "0123456789abcdef"[(value>>(i*4))&0xF];
		*ptr += + 1;
	}
}

size_t vasprintf(char * buf, const char *fmt, va_list args) {
	int i = 0;
	char *s;
	int ptr = 0;
	int len = strlen(fmt);
	for ( ; i < len && fmt[i]; ++i) {
		if (fmt[i] != '%') {
			buf[ptr++] = fmt[i];
			continue;
		}
		++i;
		unsigned int arg_width = 0;
		while (fmt[i] >= '0' && fmt[i] <= '9') {
			arg_width *= 10;
			arg_width += fmt[i] - '0';
			++i;
		}
		/* fmt[i] == '%' */
		switch (fmt[i]) {
			case 's': /* String pointer -> String */
				s = (char *)va_arg(args, char *);
				while (*s) {
					buf[ptr++] = *s++;
				}
				break;
			case 'c': /* Single character */
				buf[ptr++] = (char)va_arg(args, int);
				break;
			case 'x': /* Hexadecimal number */
				print_hex((unsigned long)va_arg(args, unsigned long), arg_width, buf, &ptr);
				break;
			case 'd': /* Decimal number */
				print_dec((unsigned long)va_arg(args, unsigned long), arg_width, buf, &ptr);
				break;
			case '%': /* Escape */
				buf[ptr++] = '%';
				break;
			default: /* Nothing at all, just dump it */
				buf[ptr++] = fmt[i];
				break;
		}
	}
	/* Ensure the buffer ends in a null */
	buf[ptr] = '\0';
	return ptr;
}

void vsprintf_helper(char * str, void (*putchar)(char), const char * format, uint32_t * pos, va_list arg) {
    char c;
    int sign, ival, sys;
    char buf[512];
    char width_str[10];
    uint32_t uval;
    uint32_t size = 8;
    uint32_t i;
    uint32_t num;
    uint32_t len;
    char* t;
    int size_override = 0;
    memset(buf, 0, 512);

    while((c = *format++) != 0) {
        sign = 0;

        if(c == '%') {
            c = *format++;
            switch(c) {
                // Handle calls like printf("%08x", 0xaa);
                case '0':
                    size_override = 1;
                    // Get the number between 0 and (x/d/p...)
                    i = 0;
                    c = *format;
                    while(!is_format_letter(c)) {
                        width_str[i++] = c;
                        format++;
                        c = *format;
                    }
                    width_str[i] = 0;
                    format++;
                    // Convert to a number
                    size = atoi(width_str);
                case 'd':
                    num=va_arg(arg, int);
                    itoa(num, buf, 10);
                    len=strlen(buf);
                    if(!size_override) size=len;
                    t=buf;
                    while (*t) {
                        putchar(*t);
                        t++;
                    }
                    break;
                case 'u':
                    num=va_arg(arg, int);
                    itoa(num, buf, 10);
                    len=strlen(buf);
                    if(!size_override) size=len;
                    t=buf;
                    while (*t) {
                        putchar(*t);
                        t++;
                    }
                    break;
                case 'x':
                    // print_hex(arg, arg_width);
                case 'p':
                    if(c == 'd' || c == 'u')
                        sys = 10;
                    else
                        sys = 16;

                    uval = ival = va_arg(arg, int);
                    if(c == 'd' && ival < 0) {
                        sign= 1;
                        uval = -ival;
                    }
                    //itoa(buf, uval, sys);
                    itoa(uval, buf, sys);
                    len = strlen(buf);
                    // If use did not specify width, then just use len = width
                    if(!size_override) size = len;
                    if((c == 'x' || c == 'p' || c == 'd') &&len < size) {
                        for(i = 0; i < len; i++) {
                            buf[size - 1 - i] = buf[len - 1 - i];
                        }
                        for(i = 0; i < size - len; i++) {
                            buf[i] = '0';
                        }
                    }
                    if(c == 'd' && sign) {
                        if(str) {
                            *(str + *pos) = '-';
                            *pos = *pos + 1;
                        }
                        else
                            (*putchar)('-');
                    }
                    if(str) {
                        strcpy(str + *pos, buf);
                        *pos = *pos + strlen(buf);
                    }
                    else {
                        char * t = buf;
                        while(*t) {
                            putchar(*t);
                            t++;
                        }
                    }
                    break;
                case 'c':
                    if(str) {
                        *(str + *pos) = (char)va_arg(arg, int);
                        *pos = *pos + 1;
                    }
                    else {
                        (*putchar)((char)va_arg(arg, int));
                    }
                    break;
                case 's':
                    if(str) {
                        char * t = (char *) va_arg(arg, int);
                        strcpy(str + (*pos), t);
                        *pos = *pos + strlen(t);
                    }
                    else {
                        char * t = (char *) va_arg(arg, int);
                        while(*t) {
                            putchar(*t);
                            t++;
                        }
                    }
                    break;
                default:
                    break;
            }
            continue;
        }
        if(str) {
            *(str + *pos) = c;
            *pos = *pos + 1;
        }
        else {
            (*putchar)(c);
        }

    }
}

char* sprintf(char* buff, const char* str, ...) {
    va_list ap;
    va_start(ap, str);
    vasprintf(buff, str, ap);
    va_end(ap);
    return buff;
}