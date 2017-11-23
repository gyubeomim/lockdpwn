/*
  c tcpip ==> connected UDP 소켓을 이용한 예제 코드
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message);

void main(int argc, char *argv[])
{
  int sock;
  char message[BUF_SIZE];
  int str_len;
  struct sockaddr_in serv_adr;

  if (argc != 3)
  {
    printf("usage");
    exit(1);
  }

  sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock == -1)
  {
    error_handling("socket() error");
  }

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_adr.sin_port = htons(atoi(argv[2]));

  connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

  while (1)
  {
    fputs("insert msg : " , stdout);
    fgets(message, sizeof(message), stdin);

    if (!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
    {
      break;
    }

    write(sock, message, strlen(message));
    str_len = read(sock, message, sizeof(message)-1);
    message[str_len] = 0;

    printf("msg from server: %s",message);
  }

  close(sock);
}

void error_handling(char *message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
