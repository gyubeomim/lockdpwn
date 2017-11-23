/*
  c tcpip ==> 파일 디스크럽터를 dup() 함수로 복사하고 스트림을 분리해본 예제 코드
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void main(int argc, char *argv[])
{
  int serv_sock, clnt_sock;
  FILE *readfp;
  FILE *writefp;

  struct sockaddr_in serv_adr, clnt_adr;
  socklen_t clnt_adr_sz;
  char buf[BUF_SIZE];

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);

  if (serv_sock == -1)
  {
    printf("fail socket");
  }

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(atoi(argv[1]));

  if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
  {
    printf("fail binding");
  }

  if(listen(serv_sock, 5) == -1)
  {
    printf("fail listening");
  }

  clnt_adr_sz = sizeof(clnt_adr);
  clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

  if (clnt_sock == -1)
  {
    printf("fail clnt_socok");
  }

  readfp = fdopen(clnt_sock, "r");
  writefp = fdopen(dup(clnt_sock), "w");

  fputs("from server: hi client\n", writefp);
  fputs("im edward\n", writefp);
  fputs("you are awesome man \n", writefp);
  fflush(writefp);

  shutdown(fileno(writefp), SHUT_WR);
  fclose(writefp);

  fgets(buf , sizeof(buf), readfp);
  fputs(buf , stdout);
  fclose(readfp);
}
