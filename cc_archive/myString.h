#ifndef __MYSTRING_H__


#define __MYSTRING_H__


#include <stdio.h>
#define STR_MAX 100

int strLen(char* str);
int strCpy(char* dest, char *source);
int strCat(char *dest, char *source);
int strCmp(char *str1, char *str2);


#endif


