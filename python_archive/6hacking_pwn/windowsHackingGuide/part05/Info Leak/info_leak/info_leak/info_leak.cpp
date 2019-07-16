#include "stdafx.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <winsock2.h>

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

class MyString 
{
private:
	int len;
	char strings[100];
	
public:
	MyString(char * _strings)
	{
		len = strlen(_strings);
		strcpy(strings,_strings);
	}

	void PrintString(void)
	{
		for(int i=0;i<len;i++)
		{
			printf("[%i] : 0x%x %c\n", i,strings[i],strings[i]);
		}
	}
};

int main(int argc, char *argv[])
{
	static char read_buf[2000] = {0,};
	static char buf[1000] = {0,};
	static Book mybook("windows_hacking",1);
	static MyString m_str1("Hello1~!");
	
	printf("buf addr    : 0x%x\n", &buf);
	printf("mstr1 addr   : 0x%x\n", &m_str1);
	printf("object addr : 0x%x\n", &mybook);
	
	printf("Before : \n");
	m_str1.PrintString();

	FILE *f = fopen(argv[1], "r");
	fgets(read_buf,2000,f);

	strcpy(buf, read_buf);

	printf("After : \n");
	m_str1.PrintString();

	mybook.setName(buf);
    return 0;
}
