#include <stdio.h>


void main()
{
  
  char c;
  int i= 0;
  
  while(1)
  {
    fputs("data input (ctrl+z to exit) : ", stdout);
    c = getchar();

    if(c == EOF)
    {
      break;
    }
  

    fflush(stdin);
    i++;
    
  }

    

  printf("%d\n",i);
  
  


}
