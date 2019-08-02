#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error_handling(char *msg);

void main(int argc, char *argv[])
{
  int fd;
  char buf[] = "Let's go!\n";

  fd = open("data.txt", O_CREAT | O_WRONLY | O_TRUNC);

  if(fd == -1)
  {
    error_handling("open() error");
  }

  printf("file descriptor : %d \n", fd);

  if(write(fd, buf, sizeof(buf)) == -1)
  {
    error_handling("write() error");
  }
  close(fd);

}

void error_handling(char *msg)
{
  fputs(msg, stderr);
  fputc('\n', stderr);
  exit(1);
}
