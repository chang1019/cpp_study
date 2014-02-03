#ifndef _STRUTIL_H_
#define _STRUTIL_H_

#include <string.h>

namespace practice {
////////////////////////////////////////////////////////////////////////////////

unsigned int getStrLen(const char* str);

const char* copyCStr(const char* str, unsigned int len = 0);

const char* intToCStr(int number);

////////////////////////////////////////////////////////////////////////////////
} // namespace practice

#endif
