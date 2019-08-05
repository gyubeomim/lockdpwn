#include <stdio.h>

int i,j,n;

int main(int argc, char **argv){
  scanf("%d", &n);

  for (i=0; i<n; i++) {
    for (j=0; j < 2*n + (i&1); j++) {
      putchar((i+j) & 1 ? 32 : 42);  // ascii : 32 ==> SPACE
    }                                //         42 ==> *
    puts("");
  }

  return 0;
}
