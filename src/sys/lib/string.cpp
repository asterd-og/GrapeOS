#include <sys/lib/string.h>
#include <sys/lib/math.h>

/* MODIFY */
void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}

char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}

/* INTEGERS AND ASCIIS */
char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // consider the absolute value of the number
    int n = abs(value);
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

int atoi(const char* S) {
    int num = 0;
 
    int i = 0;
 
    // run till the end of the string is reached, or the
    // current character is non-numeric
    while (S[i] && (S[i] >= '0' && S[i] <= '9'))
    {
        num = num * 10 + (S[i] - '0');
        i++;
    }
 
    return num;
}

/* STRINGS */

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

char* get_after(char* str, char* start)
{
    char* p = strstr(str, start);
    if(p == NULL)
        return NULL;
    p += strlen(start);
    return p;
}

bool str_has(char* str, char c) {
    for (int i=0;i<strlen(str);i++) {
        if (str[i]==c) return true;
    }
    return false;
}

char* get_inbetween(char* str, char* start, char* end)
{
    char* p = strstr(str, start);
    if(p == NULL)
        return NULL;
    p += strlen(start);
    char* q = strstr(p, end);
    if(q == NULL)
        return NULL;
    *q = '\0';
    return p;
}

char *strchr(register const char *s, int c)
{
  do {
    if (*s == c)
      {
        return (char*)s;
      }
  } while (*s++);
  return (0);
}

char *strpbrk(const char *s1, const char *s2)
{
    //return null if any one is NULL
    if((s1 == NULL) || (s2 == NULL))
        return NULL;
    while(*s1)
    {
        //return s1 char position if found in s2
        //if not found return NULL
        if(strchr(s2, *s1))
        {
            //return from function
            //if char found in s2
            return s1;
        }
        else
        {
            s1++;
        }
    }
    return NULL;
}

char *strsep(char **stringp, const char *delim) {
  if (*stringp == NULL) { return NULL; }
  char *token_start = *stringp;
  *stringp = strpbrk(token_start, delim);
  if (*stringp) {
    **stringp = '\0';
    (*stringp)++;
  }
  return token_start;
}

bool startsWith(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}

char *strcpy(char *dest, const char *src)
{
	do {
		*dest++ = *src++;
	} while (*src != 0);
}

char* strcat(char* destination, const char* source)
{
    // make `ptr` point to the end of the destination string
    char* ptr = destination + strlen(destination);
 
    // appends characters of the source to the destination string
    while (*source != '\0') {
        *ptr++ = *source++;
    }
 
    // null terminate destination string
    *ptr = '\0';
 
    // the destination is returned by standard `strcat()`
    return destination;
}

size_t str_backspace(char* str, char c)
{
	size_t i = strlen(str);
	i--;
	while(i)
	{
		i--;
		if(str[i] == c)
		{
			str[i+1] = 0;
			return 1;
		}
	}
	return 0;
}

int strcmp(const char *dst, char *src)
{
    int i = 0;

    while ((dst[i] == src[i])) {
        if (src[i++] == 0)
            return 0;
    }

    return 1;
}

size_t strsplit(char* str, char delim)
{
	size_t n = 0;
	uint32_t i = 0;
	while(str[i])
	{
		if(str[i] == delim)
		{
			str[i] = 0;
			n++;
		}
		i++;
	}
	n++;
	return n;
}

int strnum(const char* str, int base)
{
    int ret = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            ret = ret * base + str[i] - '0';
        }
        else if (str[i] >= 'a' && str[i] <= 'z')
        {
            ret = ret * base + str[i] - 'a' + 10;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            ret = ret * base + str[i] - 'A' + 10;
        }
        i++;
    }
    return ret;
}
int stroct(const char* str)
{
    return strnum(str, 8);
}

int iscntrl(int c)
{ 
    if (c >= 0 && c <= 31) { return true; }
    if (c == 127) { return true; }
    return false;
}

int isprint(int c)
{ 
    if (!iscntrl(c)) { return true; } 
    return false;
}

const char* strstr(const char* X, const char* Y)
{
    while (*X != '\0')
    {
        if ((*X == *Y) && strcmp(X, Y)) {
            return X;
        }
        X++;
    }
 
    return NULL;
}

/* MEM */

int memcmp(const void *s1, const void *s2, int len)
{
    unsigned char *p = s1;
    unsigned char *q = s2;
    int charCompareStatus = 0;
    //If both pointer pointing same memory block
    if (s1 == s2)
    {
        return charCompareStatus;
    }
    while (len > 0)
    {
        if (*p != *q)
        {  //compare the mismatching character
            charCompareStatus = (*p >*q)?1:-1;
            break;
        }
        len--;
        p++;
        q++;
    }
    return charCompareStatus;
}

void* memcpyl(void* dest, const void* src, size_t size)
{
    size_t l = size/4;
    asm volatile("cld;rep movsl" : "+D"(dest), "+S"(src), "+c"(l) : : "memory");
    return dest;
}
void* memcpyw(void* dest, const void* src, size_t size)
{
    size_t l = size/2;
    asm volatile("cld;rep movsw" : "+D"(dest), "+S"(src), "+c"(l) : : "memory");
    return dest;
}
void* memcpyb(void* dest, const void* src, size_t size)
{
    asm volatile("cld;rep movsb" : "+D"(dest), "+S"(src), "+c"(size) : : "memory");
    return dest;
}
void* memcpy(void* dest, const void* src, size_t size)
{
    if (size % 4 == 0) return memcpyl(dest, src, size);
    else if (size % 2 == 0) return memcpyw(dest, src, size);
    else return memcpyb(dest, src, size);
}

void* memsetl(void* dest, uint32_t data, size_t size)
{
    size_t l = size / 4;
    asm volatile("cld;rep stosl" : "+D"(dest), "+c"(l) : "a"(data) : "memory");
    return dest;
}
void* memsetw(void* dest, uint16_t data, size_t size)
{
    size_t l = size/2;
    asm volatile("cld;rep stosw" : "+D"(dest), "+c"(l) : "a"(data) : "memory");
    return dest;
}
void* memsetb(void* dest, uint8_t data, size_t size)
{
    asm volatile("cld;rep stosb" : "+D"(dest), "+c"(size) : "a"(data) : "memory");
    return dest;
}
void* memset(void* dest, int data, size_t size)
{
    if (size % 4 == 0) return memsetl(dest, data, size);
    else if (size % 2 == 0) return memsetw(dest, data, size);
    else return memsetb(dest, data, size);
}