#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* MODIFY  */
void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);

/* INTEGERS AND ASCIIS */
char* itoa(int value, char* buffer, int base);
int atoi(const char* S);

/* STRINGS */
char *strcpy(char *dest, const char *src);
char* get_after(char* str, char* start);
char* get_inbetween(char* str, char* start, char* end);
bool  str_has(char* str, char c);
char *strchr (register const char *s, int c);
char *strpbrk(const char *s1, const char *s2);
char *strsep(char **stringp, const char *delim);
bool startsWith(const char *pre, const char *str);
char* strcat(char* destination, const char* source);
size_t strlen(const char* str);
size_t str_backspace(char* str, char c);
int strcmp(const char *dst, char *src);
size_t strsplit(char* str, char delim);
int strnum(const char* str, int base);
int stroct(const char* str);
int isprint(int c);
const char* strstr(const char* X, const char* Y);

/* MEM */
int memcmp(const void *s1, const void *s2, int len);
void* memcpy(void* dest, const void* src, size_t size);
void * memset(void * b, int val, size_t count);
void* memsetl(void* dest, uint32_t data, size_t size);