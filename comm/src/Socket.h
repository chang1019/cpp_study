#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/socket.h>

#include "Byte.h"
#include "InetAddress.h"
#include "ServerSocket.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

/**
 * Socket class.
 * (INET only at present).
 */
class Socket {
  friend class ServerSocket;
private:
  enum {
    CLOSED = 0,
    CONNECTED,
  } status_;
  int sock_;

private:
  Socket(int sock);

public:
  ~Socket();

private:
  Socket(const Socket&);
  Socket& operator=(const Socket&);

public:
  int connect(InetAddress& address);
  int send(const Byte* message, unsigned int size);
  int recieve(Byte* message, unsigned int size);
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
