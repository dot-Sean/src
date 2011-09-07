struct UrlInfo {
    char protocol[16];
    char user[256];
    char password[256];
    char host[256];
    int port;
    char path[1024];
};

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define SUCCESS 1
#define FAILURE 0

int parseUrl(const char * url, struct UrlInfo * pinfo) {
  int iUrl = 0;
  int i;
  char * psz;
    /* ------------------------------------------------------------ */
    i = 0;
    psz = pinfo->protocol
    while (isalpha(url[iUrl])) {
        psz[i ++] = url[iUrl ++];
    }
    /* ------------------------------------------------------------ */
    while (     
}

if ftp://knaka:password@localhost:21/pub =~ ^(.+)://
  protocol = "ftp"
else
  protocol = def_protocol
  error?

if knaka:password@localhost:21/pub =~ (/.*)
  path = "/pub"
else
  path = "/"
  error?
if knaka:password@localhost:21 =~ :([0-9]+)
  port = "21"
else
  port = defports[protocol]
if knaka:password@localhost =~ @(.+)
  host = "localhost"
else if localhost =~ (.+)
  host = "localhost"
if knaka:password =~ ([^:]+):
  user = "knaka"
else
  user = "anonymous"
if password
  password = "password"
else
  password = "nopassword"

