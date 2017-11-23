/*
  c tcpip ==> operand client 구현한 예제코드
               숫자와 연산자를 서버로 보내서 결과값을 돌려받는다
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4
#define RLT_SIZE 4

void error_handling(char *message);

void main(int argc, char *argv[])
{
  int sock;
  char opmsg[BUF_SIZE];
  int result, opnd_cnt, i;

  struct sockaddr_in serv_adr;
  if (argc != 3)
  {
    printf("nope");
    exit(1);
  }

  sock = socket(PF_INET, SOCK_STREAM,0);
  if (sock == -1)
  {
    error_handling("socket() error");
  }

  memset(&serv_adr, 0, sizeof(serv_adr));
  serv_adr.sin_family = AF_INET;
  serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_adr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
  {
    error_handling("connect() error");
  }
  else
  {
    puts("conneted...");
  }

  fputs("operand count : ", stdout);
  scanf("%d", &opnd_cnt);
  opmsg[0] = (char)opnd_cnt;

  for (i = 0; i < opnd_cnt; i++)
  {
    printf("operand %d: ", i+1);
    scanf("%d", (int*)&opmsg[i*OPSZ + 1]);
  }

  fgetc(stdin);
  fputs("Operator: ", stdout);
  scanf("%c", &opmsg[opnd_cnt * OPSZ + 1]);
  write(sock, opmsg, opnd_cnt*OPSZ + 2);
  read(sock, &result, RLT_SIZE);

  printf("operation results: %d\n",result);
  close(sock);
}

void error_handling(char *message)
{
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
