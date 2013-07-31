/* Alex Pennace */
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>

int pick_addr(const char *node, const char *service, struct addrinfo *saddr) {
  register int ret, count, pick, i;
  struct addrinfo *addrs, *addr, hints = {0};

  hints.ai_family = AF_UNSPEC; /* I wonder if POSIX defines AF_UNSPEC
				  to be 0, in which case we can omit
				  this line. */
  hints.ai_socktype = SOCK_STREAM;

  ret = getaddrinfo(node, service, &hints, &addrs);
  if(ret)
    return -1;

  for(count = 0, addr = addrs; addr; count++, addr = addr->ai_next);

  pick = rand() % count;

  for(i = 0, addr = addrs; i < pick; i++, addr = addr->ai_next);

  *saddr = *addr;
  saddr->ai_next = NULL;

  freeaddrinfo(addrs);

  return 0;
  
}

int main(int argc, char *argv[]) {
  struct addrinfo addr;

  srand(time(NULL));

  pick_addr("irc.efnet.net", "6667", &addr);

  switch(addr.ai_family) {
  case AF_INET: printf("ai_family: AF_INET\n"); break;
  case AF_INET6: printf("ai_family: AF_INET6\n"); break;
  default:
    printf("ai_family: unknown\n");
  }

  switch(addr.ai_socktype) {
  case SOCK_STREAM: printf("ai_socktype: SOCK_STREAM\n"); break;
  case SOCK_DGRAM: printf("ai_socktype: SOCK_DGRAM\n"); break;
  default:
    printf("ai_socktype: unknown\n");
  }

  printf("ai_protocol: %d\n", addr.ai_protocol);

  return 0;
}
