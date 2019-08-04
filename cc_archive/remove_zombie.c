/*
  c tcpip ==>
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc (int sig )
{
  int status;
  pid_t id = waitpid(-1, &status, WNOHANG);

  if (WIFEXITED(status))
  {
    printf("removed proc id : %d\n", id);
    printf("child send : %d\n", WEXITSTATUS(status));
  }
}

int main(int argc, char *argv[])
{
  pid_t pid;
  struct sigaction act;
  act.sa_handler = read_childproc;
  sigemptyset(&act.sa_mask);
  act.sa_flags=0;
  sigaction(SIGCHLD, &act, 0);

  pid = fork();
  if (pid == 0)
  {
    puts("i'm child");
    sleep(10);
    return 12;
  }
  else
  {
    printf("child proc id: %d\n",pid);
    pid = fork();
    if (pid == 0)
    {
      puts("i'm child2");
      sleep(10);
      exit(24);
    }
    else
    {
      int i;
      printf("child proc id2: %d\n",pid);
      for (i = 0; i<5; i++)
      {
        puts("wait...");
        sleep(5);
      }
    }
  }

  return 0;
}
