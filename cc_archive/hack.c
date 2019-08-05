/*
  c ftz ==> 공유메모리 영역을 읽어서 level10을 푸는 예제 코드
 */
#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>

#define B_SIZE 1024

void main()
{
  void *sharedMem = (void*)0;
  int sharedMemID;
  char buf[B_SIZE];
  key_t keyval = 7530;

  sharedMemID = shmget(keyval, B_SIZE, 0666);
  sharedMem = shmat(sharedMemID, (void*)0, 0);

  memcpy(buf, sharedMem, B_SIZE);
  printf("%s", buf);
  shmdt(sharedMem );

}
