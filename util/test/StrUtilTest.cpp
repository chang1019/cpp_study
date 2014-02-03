#include <gtest/gtest.h>
#include <stdio.h>

#include "StrUtil.h"

using namespace practice;

////////////////////////////////////////////////////////////////////////////////
// test util class
class StrHolder {
private:
  const char* str_;

public:
  StrHolder(const char* str) : str_(str) {}
  ~StrHolder() {
    if (NULL != str_) { delete[] str_; }
  }

  const char* operator->() { return str_; }
  const char* get() { return str_; }
};

////////////////////////////////////////////////////////////////////////////////
// tests
class StrUtilTest : public ::testing::Test {
};

TEST_F(StrUtilTest, intToCStrTest_001) {
  StrHolder zero(intToCStr(0));
  ASSERT_STREQ("0", zero.get());
}

TEST_F(StrUtilTest, intToCStrTest_002) {
  {
    StrHolder numstr(intToCStr(83478));
    ASSERT_STREQ("83478", numstr.get());
  }
  {
    StrHolder numstr(intToCStr(2147483647));
    ASSERT_STREQ("2147483647", numstr.get());
  }
}

TEST_F(StrUtilTest, IntToCStrTest_003) {
  {
    StrHolder numstr(intToCStr(-19349));
    ASSERT_STREQ("-19349", numstr.get());
  }
  {
    StrHolder numstr(intToCStr(-2147483648));
    ASSERT_STREQ("-2147483648", numstr.get());
  }
}
