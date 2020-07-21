#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>

using namespace std;

char *MakeStrAdr(int len)
{
     char * str = new char[len];
     return str;
}

int main()
{
     char *str = MakeStrAdr(100);

     strcpy(str,"I'm so nice and cool guy. right? yes. you are Eddy! Of course man!");

     cout<<str<<endl;
     cout<<strlen(str)<<endl;

     delete []str;

     return 0;
}

