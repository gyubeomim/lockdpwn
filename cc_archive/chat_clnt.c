/*
  c tcpip ==> Multi thread를 이용해 채팅클라이언트를 구현해본 예제 코드
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100
#define NAME_SIZE 20

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];

void *send_msg (void *arg)
{
  int sock = *((int*)arg);
  char name_msg[NAME_SIZE + BUF_SIZE];

  while (1)
  {
  //fgets(char* __s, int __n, FILE* __stream)
    fgets(msg, BUF_SIZE, stdin);

    if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
    {
      close(sock);
      exit(0);
    }

    sprintf(name_msg, "%s %s", name, msg);

  //write(int __fd, void* __buf, size_t __n)
    write(sock, name_msg, strlen(name_msg));
  }
  return NULL;
}

void *recv_msg (void *arg )
{
  int sock = *((int*) arg);
  char name_msg[NAME_SIZE + BUF_SIZE];
  int str_len;

  while (1)
  {
    str_len = read(sock, name_msg, NAME_SIZE + BUF_SIZE - 1);
    if (str_len == -1)
    {
      return (void*)-1;
    }
    name_msg[str_len] = 0;
    fputs(name_msg, stdout);
  }
  return NULL;
}

void error_handling (char *msg)
{
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}

int main(int argc, char *argv[])
{
  int sock;
  struct sockaddr_in serv_addr;
  pthread_t snd_thread, rcv_thread;
  void *thread_return;

  if (argc != 4)
  {
    printf("usage %s \n",argv[0]);
    exit(1);
  }

  sprintf(name , "[%s]", argv[3]);
  sock = socket(PF_INET, SOCK_STREAM, 0);

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (connect(sock , (struct sockaddr*)&serv_addr , sizeof(serv_addr)) == -1)
  {
    error_handling("connect() error");
  }

//pthread_create(pthread_t* __newthread, pthread_attr_t* __attr, void*, void* __arg)
  pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
  pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);

//pthread_join(pthread_t __th, void** __thread_return)
  pthread_join(snd_thread, &thread_return);
  pthread_join(rcv_thread, &thread_return);
  close(sock);
  return 0;
}
