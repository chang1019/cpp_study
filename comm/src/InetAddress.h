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

private:
  struct sockaddr_in addr_;

private:
  InetAddress(in_addr_t iaddr, int port);

public:
  ~InetAddress();

private:
  InetAddress(const InetAddress&);
  InetAddress& operator=(const InetAddress&);

public:
  static InetAddress* create(const char* host, int port);
};

////////////////////////////////////////////////////////////////////////////////
} //namespace

#endif
