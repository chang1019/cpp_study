#include <iostream>
#include <stdio.h>

#include <gtest/gtest.h>

#include "Socket.h"
#include "StrUtil.h"

using namespace practice;

////////////////////////////////////////////////////////////////////////////////
// test util class
class SocketHolder {
private:
  Socket* sock_;

public:
  SocketHolder(Socket* sock) : sock_(sock) {}
  ~SocketHolder() { delete sock_; }

  Socket* operator->() { return sock_; }
  Socket* get() { return sock_; }
};

class InetAddressHolder {
private:
  InetAddress* address_;

public:
  InetAddressHolder(InetAddress* address) : address_(address) {}
  ~InetAddressHolder() { delete address_; }

  InetAddress* operator->() { return address_; }
  InetAddress* get() { return address_; }
};

////////////////////////////////////////////////////////////////////////////////
// tests
class SocketTest : public ::testing::Test {
};

TEST_F(SocketTest, httpGetTest_001) {
  SocketHolder sock(Socket::createTCP());
  ASSERT_TRUE(NULL != sock.get());
  InetAddressHolder addr(InetAddress::create("www.yahoo.co.jp", 80));
  ASSERT_TRUE(NULL != addr.get());
  ASSERT_EQ(0, sock->connect(*addr.get()));

  const char* req = "GET / HTTP/1.0\r\n\r\n";
  ASSERT_TRUE(0 < sock->send(req, getStrLen(req)));

  Byte buf[4096];
  ASSERT_TRUE(0 < sock->recieve(buf, 4096));

  const char* status_success = "HTTP/1.1 200 OK";
  const char* status = copyCStr(buf, getStrLen(status_success));
  ASSERT_STREQ(status_success, status);
  delete[] status;

  ASSERT_EQ(0, sock->close());
}
