#include <iostream>
#include <stdio.h>

#include <gtest/gtest.h>

#include "ServerSocket.h"
#include "Socket.h"
#include "StrUtil.h"
#include "Thread.h"

using namespace practice;

////////////////////////////////////////////////////////////////////////////////
// test util class
class ServerSocketHolder {
private:
  ServerSocket* sock_;

public:
  ServerSocketHolder(ServerSocket* sock) : sock_(sock) {}
  ~ServerSocketHolder() { delete sock_; }

  ServerSocket* operator->() { return sock_; }
  ServerSocket* get() { return sock_; }
};

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

/**
 * Client Thread Runner
 */
class Executor : public Runnable {
public:
  Executor() {}
  ~Executor() {}

  void sendAndCheck() {
    SocketHolder sock(Socket::createTCP());
    InetAddressHolder addr(InetAddress::create("127.0.0.1", 8089));
    while (0 != sock->connect(*addr.get())) {
      std::cout << "waiting server setup..." << std::endl;
      sleep(1);
    }

    const char* message = "Hello, socket!";
    ASSERT_TRUE(0 < sock->send(message, getStrLen(message)));

    Byte buf[4096];
    ASSERT_TRUE(0 < sock->recieve(buf, 4096));
    ASSERT_STREQ(message, (char*)buf);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Implementation of Runnable.
  void* run(void* arg) {
    sendAndCheck();
    return NULL;
  }
};

////////////////////////////////////////////////////////////////////////////////
// tests
class ServerSocketTest : public ::testing::Test {
};

TEST_F(ServerSocketTest, CommunicationTest_001) {
  // client setup
  Thread thread;
  Executor executor;
  thread.start(executor, NULL);
  // server setup
  InetAddressHolder addr(InetAddress::create("127.0.0.1", 8089));
  ASSERT_TRUE(NULL != addr.get());
  ServerSocketHolder srvSock(ServerSocket::createTCP(*addr.get(), 10));
  ASSERT_TRUE(NULL != srvSock.get());

  SocketHolder sock(srvSock->accept());

  Byte buf[4096];
  int len = sock->recieve(buf, 4096);
  ASSERT_TRUE(0 < len);
  ASSERT_TRUE(0 < sock->send(buf, len));
  ASSERT_EQ(0, sock->close());
  thread.join();
}
