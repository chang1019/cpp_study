#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Socket.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

namespace {
////////////////////////////////////////////////////////////////////////////////

int call_connect(int sock, struct sockaddr* addr, unsigned int size) {
  return connect(sock, addr, size);
}

int call_send(int sock, const char* message, unsigned int size) {
  return send(sock, message, size, 0);
}

int call_close(int sock) {
  return close(sock);
}

////////////////////////////////////////////////////////////////////////////////
}

Socket::Socket(int sock)
  : status_(CLOSED),
    sock_(sock)
{}

Socket::~Socket() {
  close();
}

int Socket::connect(const char* host, int port) {
  if (CONNECTED == status_) {
    printf("[connect] fail to connect. socket has been already connected.\n");
    return -1;
  }
  if (NULL == (address_ = InetAddress::create(host, port))) {
    printf("[connect] fail to get address of the host : %s\n", host);
    return -1;
  }

  int result = call_connect(sock_,
			    address_->addr_->ai_addr,
			    address_->addr_->ai_addrlen);
  if (result < 0) {
    perror("connect");
    delete address_;
    address_ = NULL;
    return result;
  }
  status_ = CONNECTED;
  return result;
}

int Socket::send(const Byte* message, unsigned int size) {
  if (CONNECTED != status_) {
    printf("[send] fail to send message. socket is not connected any address.\n");
    return -1;
  }
  int send_size = call_send(sock_, message, size);
  if (send_size < 0) { perror("send"); }
  return send_size;
}

int Socket::recieve(Byte* message, unsigned int size) {
  if (CONNECTED != status_) {
    printf("[receive] fail to recieve message. socket is not connected any address.\n");
    return -1;
  }
  int recv_size = recv(sock_, message, size, 0);
  if (recv_size < 0) { perror("recv"); }
  if (0 < recv_size && recv_size < size) {
    memset(message + recv_size, '\0', size - recv_size);
  }
  return recv_size;
}

int Socket::close() {
  int result = 0;
  if (CLOSED != status_) {
    result = call_close(sock_);
    if (result < 0) {
      perror("close");
      return result;
    }
    delete address_;
    address_ = NULL;
    status_ = CLOSED;
  }
  return result;
}

Socket* Socket::createTCP() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("socket");
    return NULL;
  }
  return new Socket(sock);
}

Socket* Socket::createUDP() {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("socket");
    return NULL;
  }
  return new Socket(sock);
}

Socket* Socket::createRAW() {
  int sock = socket(AF_INET, SOCK_RAW, 0);
  if (sock < 0) {
    perror("socket");
    return NULL;
  }
  return new Socket(sock);
}

Socket* Socket::createICMP() {
  int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (sock < 0) {
    perror("socket");
    return NULL;
  }
  return new Socket(sock);
}

////////////////////////////////////////////////////////////////////////////////
} //namespace practice
