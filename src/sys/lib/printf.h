#pragma once

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>

int is_format_letter(char c);
void vsprintf(char * str, void (*putchar)(char), const char * format, va_list arg);
size_t vasprintf(char * buf, const char *fmt, va_list args);
void vsprintf_helper(char * str, void (*putchar)(char), const char * format, uint32_t * pos, va_list arg);
char* sprintf(char* buff, const char* str, ...);