#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

#include "InetAddress.h"

namespace practice {
////////////////////////////////////////////////////////////////////////////////

InetAddress::InetAddress(in_addr_t iaddr, int port)
  : addr_()
{
  memset(&addr_, '\0', sizeof(addr_));
  addr_.sin_family = AF_INET;
  addr_.sin_port = htons(port);
  addr_.sin_addr.s_addr = iaddr;
}

InetAddress::~InetAddress() {}

InetAddress* InetAddress::create(const char* host, int port) {
  in_addr_t iaddr = inet_addr(host);
  if (INADDR_NONE == iaddr) {
    // FIXME : replace with getaddrinfo
    struct hostent* host_ptr = gethostbyname(host);
    if (NULL == host_ptr) {
      herror("gethostbyname");
      return NULL;
    }

    struct in_addr* sin_addr = (struct in_addr*)host_ptr->h_addr;
    iaddr = sin_addr->s_addr;
  }
  return new InetAddress(iaddr, port);
}

////////////////////////////////////////////////////////////////////////////////
} //namespace
