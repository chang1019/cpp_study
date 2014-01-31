#include "StrUtil.h"

#include <string.h>

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

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
