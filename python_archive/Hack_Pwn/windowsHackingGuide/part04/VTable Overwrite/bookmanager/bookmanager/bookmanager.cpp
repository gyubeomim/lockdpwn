#include "stdafx.h"
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;

class Book 
{
private:
	char name[100];
	int page;

public:
	Book(char * _name, int _page)
	{
		strcpy(name,_name);
		page = _page;
	}
	virtual void setName(char * input)
	{
		char * buf = (char*)malloc(20);
		strncpy(buf, input, 19);
		printname(buf);
		getName();
	}
	virtual void printname(char * buf)
	{
		printf("name : %s",buf);
	}
	virtual char * getName()
	{
		return name;
	}
};

int main(int argc, char* argv[])
{	
	if(argc!=2) 
	{
		printf(" Usage : bookmanager.exe [filename]\n");
		exit(1);
	}

	static char contents[1000] = {0,};
	static Book mybook("windows_hacking",1);
	
	printf("object addr : 0x%x\n", &mybook);
	printf("object vtable addr : 0x%p\n", mybook);
	printf("buf addr : 0x%x\n", &contents);

	FILE *f = fopen(argv[1], "r");
	fgets(contents,1500,f);
	mybook.setName(contents);

	return 0;
}

