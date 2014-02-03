#include <gtest/gtest.h>

#include "InetAddress.h"
#include "StrUtil.h"

using namespace practice;

////////////////////////////////////////////////////////////////////////////////
// test util class
class AddressHolder {
private:
  InetAddress* addr_;

public:
  AddressHolder(InetAddress* addr) : addr_(addr) {}
  ~AddressHolder() { delete addr_; }

  InetAddress* operator->() { return addr_; }
  InetAddress* get() { return addr_; }
};

////////////////////////////////////////////////////////////////////////////////
// tests
class InetAddressTest : public ::testing::Test {
};

TEST_F(InetAddressTest, createTest_001) {
  AddressHolder address(InetAddress::create("www.yahoo.co.jp", 80));
  ASSERT_TRUE(NULL != address.get());
}

TEST_F(InetAddressTest, showInfoTest_001) {
  AddressHolder address(InetAddress::create("localhost", 80));
  address->showInfo();
}
