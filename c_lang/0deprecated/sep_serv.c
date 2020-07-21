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
  char buf[BUF_SIZE] = {0 ,};

  serv_sock = socket(PF_INET, SOCK_STREAM, 0);

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_adr.sin_port = htons(atoi(argv[1]));

  bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr));
  listen(serv_sock,5);

  clnt_adr_sz = sizeof(clnt_adr);
  clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

  readfp = fdopen(clnt_sock,"r");
  writefp = fdopen(clnt_sock,"w");

  fputs("from server : hi client? \n", writefp);
  fputs("i love all of the world \n", writefp);
  fputs("you awesome man \n", writefp);
  fflush(writefp);

  fclose(writefp);
  fgets(buf, sizeof(buf), readfp);
  fputs(buf, stdout);
  fclose(readfp);
}
