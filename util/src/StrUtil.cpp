#include <stdio.h>
#include <string.h>

#include "StrUtil.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

unsigned int getStrLen(const char* str) {
  if (NULL == str) return 0;
  return strlen(str);
}

const char* copyCStr(const char* str, unsigned int len) {
  if (NULL == str) { return NULL; }

  if (0 == len) {
    int i = 0;
    char c;
    while (true) {
      c = str[i++];
      if ('\0' == c) { break; }
    }
    len = i - 1;
  }

  char* ret = new char[len + 1];
  strncpy(ret, str, len);
  ret[len] = '\0';
  return ret;
}

namespace {

char hexstr[16 + 1] = "0123456789abcdef";

}

// expected range [-2147483648, 2147483647]
const char* intToCStr(int number) {
  bool sign = number < 0;

  char buf[11];
  char* p = buf + 10;

  int quot = number;
  int mod;
  while (true) {
    mod = quot % 10;
    quot /= 10;
    *p = hexstr[(sign) ? -mod : mod];
    if (0 == quot) { break; }
    p--;
  }

  if (sign) { *(--p) = '-'; }
  unsigned int len = 11 - (p - buf);
  return copyCStr(p, len);
}

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
