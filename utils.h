#ifndef BARESNAKE_UTILS_H
#define BARESNAKE_UTILS_H

#include <stddef.h>

size_t strlen(const char* str);
void strrev(char* str);

void* memset(void* s, int c, size_t n);

int itoa(int num, char* str, int len, int base);

#endif
