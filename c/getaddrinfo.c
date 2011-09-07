#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
                     
int 
main (
  int argc,
  char * * argv ) {
  int s;
  struct addrinfo hints, * res, * res0;
    memset(&hints, 0, sizeof(hints));
#if 1
    hints.ai_family = PF_UNSPEC;
#else
    hints.ai_family = PF_INET;
#endif
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo("www.google.com", "http", & hints, & res0);
    for (res = res0; res; res = res->ai_next) {
        s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (connect(s, res->ai_addr, res->ai_addrlen) < 0) {
           close(s);
           continue;
        }
        break;
    }
    freeaddrinfo(res0);
    return (0);
}
