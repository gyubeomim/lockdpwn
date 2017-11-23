/*
  c tcpip ==> 시스템함수 read, write를 사용해 데이터 전송속도를 확인하는 예제 코드
             느리다고 한다
 */
#include <stdio.h>
#include <fcntl.h>

#define BUF_SIZE 3

int main(int argc, char *argv[])
{
  int fd1, fd2;
  int len;
  char buf[BUF_SIZE];

  fd1 = open("news.txt", O_RDONLY);
  fd2 = open("cpy.txt", O_WRONLY | O_CREAT | O_TRUNC);

  while ((len = read(fd1, buf, sizeof(buf))) > 0 )
  {
    write(fd2, buf, len);
  }

  close(fd1);
  close(fd2);
  return 0;
}
