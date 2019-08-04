#include <stdio.h>
#include <arpa/inet.h>

void main(int argc, char *argv[])
{
  char *addr1 = "1.2.3.4";
  char *addr2 = "1.2.3.256";

  unsigned long conv_addr = inet_addr(addr1);

  if(conv_addr == INADDR_NONE)
  {
    printf("error\n");
  }
  else
  {
    printf("network ordered interger addr : %#1x \n", conv_addr);
  }

  conv_addr = inet_addr(addr2);
  if (conv_addr == INADDR_NONE)
  {
    printf("error\n");
  }
  else
  {
    printf("network ordered interger addr : %#1x \n", conv_addr);
  }

}
