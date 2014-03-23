#ifndef _ADDRESS_H_
#define _ADDRESS_H_

#include <netinet/in.h>

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * InetAddress class.
 */
class InetAddress {
  friend class Socket;
  friend class ServerSocket;

private:
  struct addrinfo* addr_;

private:
  InetAddress(struct addrinfo* addr);

public:
  ~InetAddress();

private:
  InetAddress(const InetAddress&);
  InetAddress& operator=(const InetAddress&);

public:
  void showInfo();

public:
  static InetAddress* create(const char* host, int port);
};

////////////////////////////////////////////////////////////////////////////////
} //namespace

#endif
