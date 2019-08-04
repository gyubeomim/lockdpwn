#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

char *MakeStrAdr(int len)
{
  char * str = (char*)malloc(sizeof(char)*len);
  return str;
}

int main()
{
  char *str = MakeStrAdr(60);

  strcpy(str,"I'm so nice and cool guy. right?");

  cout<<str<<endl;
  cout<<strlen(str)<<endl;

  free(str);

  return 0;
}
