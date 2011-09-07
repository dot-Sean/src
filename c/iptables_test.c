#include <stdio.h>
#include <string.h>

#include <sys/types.h> 
#include <sys/socket.h> 
#include <linux/in.h>
#include <linux/if.h>
#include <linux/netfilter_ipv4/ip_tables.h>

int main () {
  int iFd;
  int nLen;
  struct ipt_getinfo info;
    iFd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    printf("d0: %d\n", iFd);
    strcpy(info.name, "mangle");
    nLen = sizeof(info);
    if (getsockopt(iFd, IPPROTO_IP, IPT_SO_GET_INFO, & info, & nLen) >= 0) {
        printf("d: %d\n", (int) info.valid_hooks);
    }
    return (0);
}
