#include "utils.h"

size_t strlen(const char* str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}

void strrev(char* str) {
  int i, j;
  char a;
  size_t len = strlen(str);

  for (i = 0, j = len - 1; i < j; i++, j--) {
    a = str[i];
    str[i] = str[j];
    str[j] = a;
  }
}

void* memset(void* s, int c, size_t n) {
  unsigned char* p = s;

  while (n-- > 0)
    *p++ = c;

  return s;
}

int itoa(int num, char* str, int len, int base) {
  int sum = num;
  int i = 0;
  int digit;

  if (len == 0)
    return -1;

  do {
    digit = sum % base;

    if (digit < 0xA) {
      str[i++] = '0' + digit;
    } else {
      str[i++] = 'A' + digit - 0xA;
    }

    sum /= base;
  } while (sum && (i < (len - 1)));

  if (i == (len - 1) && sum)
    return -1;

  str[i] = '\0';
  strrev(str);

  return 0;
}
