#include <iostream>

#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ServerSocket.h"
#include "Socket.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

namespace {
////////////////////////////////////////////////////////////////////////////////

int call_accept(int sock, struct sockaddr* addr, unsigned int* size) {
  return accept(sock, addr, size);
}

int call_close(int sock) {
  return close(sock);
}

////////////////////////////////////////////////////////////////////////////////
}

ServerSocket::ServerSocket(int sock, int backlog)
  : status_(CLOSED),
    sock_(sock),
    backlog_(backlog)
{}

ServerSocket::~ServerSocket() {
  close();
}

Socket* ServerSocket::accept() {
  if (CONNECTED != status_) {
    if (0 != listen(sock_, backlog_)) {
      perror("listen");
      return NULL;
    }
    status_ = CONNECTED;
  }

  struct sockaddr_in client_addr;
  memset(&client_addr, '\0', sizeof(struct sockaddr_in));
  unsigned int client_addrlen = 0;
  int client_sock = call_accept(sock_, (struct sockaddr*)&client_addr, &client_addrlen);
  if (client_sock < 0) {
    perror("accept");
    return NULL;
  }

  Socket* sock = new Socket(client_sock);
  sock->status_ = Socket::CONNECTED;
  return sock;
}

int ServerSocket::close() {
  int result = 0;
  if (CLOSED != status_) {
    result = call_close(sock_);
    if (result < 0) {
      perror("close");
      return result;
    }
    status_ = CLOSED;
  }
  return result;
}

ServerSocket* ServerSocket::createTCP(InetAddress& address, int backlog, bool isAddressReusable) {
  if (backlog < 1) {
    printf("[createTCP] invalid parameter of backlog : %d", backlog);
    return NULL;
  }

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("socket");
    return NULL;
  }

  if (isAddressReusable) {
    int on = 1;
    int result = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (0 != result) {
      perror("setsockopt");
      return NULL;
    }
  }

  if (0 != bind(sock, address.addr_->ai_addr, address.addr_->ai_addrlen)) {
    perror("bind");
    return NULL;
  }

  return new ServerSocket(sock, backlog);
}

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
