#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_main (void *arg)
{
  int i;
  int cnt = *((int*)arg);
  char *msg = (char*)malloc(sizeof(char)*50);

  strcpy(msg, "hello, I'm thread");

  for (i = 0; i < cnt; i++)
  {
    sleep(1);
    puts("running thread");
  }
  return (void*)msg;
}

int main(int argc, char *argv[])
{
  pthread_t t_id;  // unsinged long int
  int thread_params = 5;
  void *thr_ret;

  if(pthread_create(&t_id, NULL, thread_main, (void*)&thread_params) != 0)
  {
    puts("pthread_create() error");
    return -1;
  }

  if (pthread_join(t_id, &thr_ret) != 0)
  {
    puts("pthread_join() error");
    return -1;
  }

  printf("thread return message: %s\n", (char*)thr_ret);
  free(thr_ret);
  return 0;
}
