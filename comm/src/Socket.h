#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/socket.h>

#include "InetAddress.h"
#include "Byte.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * Socket class.
 * (INET only at present).
 */
class Socket {
private:
  enum {
    CLOSED = 0,
    CONNECTED,
  } status_;
  int sock_;
  InetAddress* address_;

private:
  Socket(int sock);

public:
  ~Socket();

private:
  Socket(const Socket&);
  Socket& operator=(const Socket&);

public:
  int connect(const char* host, int port);
  int send(const Byte* request, unsigned int size);
  int recieve(Byte* response, unsigned int size);
  int close();

public:
  /**
   * static factory method for tcp/ip socket.
   */
  static Socket* createTCP();
  /**
   * static factory method for udp/ip socket.
   */
  static Socket* createUDP();
  /**
   * static factory method for ip socket.
   */
  static Socket* createRAW();
  /**
   * static factory method for icmp socket.
   */
  static Socket* createICMP();
};

////////////////////////////////////////////////////////////////////////////////
} //namespace

#endif
