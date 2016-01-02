#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void)
{
       in_addr_t addr = inet_addr("127.0.0.1");
       struct hostent *hent;

       hent = gethostent();
       if (hent == NULL) {
               printf("gethostent(%d):%s\n", errno, hstrerror(h_errno));
               exit(1);
       }

       hent = gethostbyname("localhost");
       if (hent == NULL) {
               printf("gethostbyname(%d):%s\n", errno, hstrerror(h_errno));
               exit(1);
       }

       hent = gethostbyname2("localhost", AF_INET);
       if (hent == NULL) {
               printf("gethostbyname2(%d):%s\n", errno, hstrerror(h_errno));
               exit(1);
       }

       hent = gethostbyaddr(&addr, sizeof(addr), AF_INET);
       if (hent == NULL) {
               printf("gethostbyaddr(%d):%s\n", errno, hstrerror(h_errno));
               exit(1);
       }

       return 0;
}

