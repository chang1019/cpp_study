#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include "InetAddress.h"
#include "StrUtil.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

InetAddress::InetAddress(struct addrinfo* addr)
  : addr_(addr)
{}

InetAddress::~InetAddress() {
  freeaddrinfo(addr_);
}

void InetAddress::showInfo() {
  char address[INET6_ADDRSTRLEN];
  struct addrinfo* addrp = NULL;
  for (addrp = addr_; NULL != addrp; addrp = addrp->ai_next) {
    printf("ai_family:\t%d\n", addrp->ai_family);
    printf("ai_socktype:\t%d\n", addrp->ai_socktype);
    printf("ai_protocol:\t%d\n", addrp->ai_protocol);
    printf("ai_addrlen:\t%d\n", addrp->ai_addrlen);
    printf("ai_canonname:\t%s\n", addrp->ai_canonname);
    if (AF_INET == addrp->ai_family) {
      struct sockaddr_in* addr_in = (struct sockaddr_in*)addrp->ai_addr;
      struct in_addr ia = { addr_in->sin_addr.s_addr };
      if (NULL == inet_ntop(addrp->ai_family,
			    &ia,
			    address,
			    addrp->ai_addrlen)) {
	perror("inet_ntop");
	return;
      }
      printf("ai_addr:\t%s : %d\n", address, ntohs(addr_in->sin_port));
    }
    else if (AF_INET6 == addrp->ai_family) {
      struct sockaddr_in6* addr_in = (struct sockaddr_in6*)addrp->ai_addr;
      struct in6_addr ia = addr_in->sin6_addr;
      if (NULL == inet_ntop(addrp->ai_family,
			    &ia,
			    address,
			    addrp->ai_addrlen)) {
	perror("inet_ntop");
	return;
      }
      printf("ai_addr:\t%s : %d\n", address, ntohs(addr_in->sin6_port));
    }
  }
}

InetAddress* InetAddress::create(const char* host, int port) {
  struct addrinfo hints;
  memset(&hints, '\0', sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  struct addrinfo* res = NULL;
  const char* portstr = intToCStr(port);
  int result = getaddrinfo(host, portstr, &hints, &res);
  delete[] portstr;
  if (result < 0) {
    perror("getaddrinfo");
    freeaddrinfo(res);
    return NULL;
  }

  return new InetAddress(res);
}

////////////////////////////////////////////////////////////////////////////////
} //namespace
