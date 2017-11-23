/*
  c tcpip ==>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUF_SIZE 30

void error_handling(char *message);

void main(int argc, char *argv[])
{
  int i;
  struct hostent *host;

  if (argc != 2)
  {
   printf("usage");
   exit(1);
  }

  host = gethostbyname(argv[1]);
  if (!host)
  {
    error_handling("gethost error");
  }

  printf("official name : %s\n", host->h_name);
  for (i = 0; host->h_aliases[i]; i++)
  {
    printf("aliases %d : %s\n", i+1, host->h_aliases[i]);
  }

  printf("address type : %s\n",(host->h_addrtype == AF_INET)? "AF_INET" :"AF_INET6" );

  for (i = 0; host->h_addr_list[i]; i++)
  {
    printf("ip addr %d : %s\n", i+1,
           inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
  }
}

void error_handling(char *message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
