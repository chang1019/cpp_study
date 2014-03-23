#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_

#include <sys/socket.h>

#include "Byte.h"
#include "InetAddress.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

class Socket;

/**
 * ServerSocket class.
 * (INET only at present).
 */
class ServerSocket {
private:
  enum {
    CLOSED = 0,
    CONNECTED,
  } status_;
  int sock_;
  int backlog_;

private:
  ServerSocket(int sock, int backlog);

public:
  ~ServerSocket();

private:
  ServerSocket(const ServerSocket&);
  ServerSocket& operator=(const ServerSocket&);

public:
  Socket* accept();
  int close();

public:
  /**
   * static factory method for tcp/ip socket.
   */
  static ServerSocket* createTCP(InetAddress& address, int backlog, bool isAddressReuseable = true);
};

////////////////////////////////////////////////////////////////////////////////
} //namespace

#endif
