#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <unistd.h>
#include <arpa/inet.h>

int
lookup_host (const char *host)
{
  struct addrinfo hints, *res, *rp;
  int errcode;
  char addrstr[100];
  void *ptr;

  memset (&hints, 0, sizeof (hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  errcode = getaddrinfo (host, NULL, &hints, &res);
  if (errcode != 0)
    {
      perror ("getaddrinfo");
      return -1;
    }

  printf ("Host: %s\n", host);
    int cnt= 0;
    for (rp = res; rp; rp = rp->ai_next)
    {
      //inet_ntop (rp->ai_family, rp->ai_addr->sa_data, addrstr, 100);

      switch (rp->ai_family)
        {
        case AF_INET:
          ptr = &((struct sockaddr_in *) rp->ai_addr)->sin_addr;
          break;
        case AF_INET6:
          ptr = &((struct sockaddr_in6 *) rp->ai_addr)->sin6_addr;
          break;
        }
      inet_ntop (rp->ai_family, ptr, addrstr, 100);
      printf ("IPv%d addrps: %s (%s)\n", rp->ai_family == PF_INET6 ? 6 : 4,
              addrstr, rp->ai_canonname);
        printf("cnt = %d\n", cnt++);
    }

  return 0;
}

int main (void)
{
  char inbuf[256];
  int len;
  bzero(inbuf, 256);
  gethostname(inbuf, 256);
  printf("hostname is %s\n", inbuf);
  if(strlen(inbuf) > 0)
    lookup_host (inbuf);
  else
    return EXIT_SUCCESS;
}
