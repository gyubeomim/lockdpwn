#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
  char readbuf[500] = {0,};
  printf(" # text reader #\n");

  if(argc!=2)
  {
    printf(" Usage : %s filename\n", argv[0]);
    exit(1);
  }

  FILE *f = fopen(argv[1], "r");
  fgets(readbuf,1000,f);
  printf("File Contents : %s\n", readbuf);

  return 0;
}
