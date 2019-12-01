/*
  clang project, 특정한 문자를 대문자화 <==> 소문자화하는 코드
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int strupr(char *);
int strlwr(char *);

int main()
{
    char string[256];

    memset(string, 0x00, sizeof(string));
    sprintf(string, "%s", "abc123defg");
    fprintf(stdout, "\"%s\"\n", string);


    // 사용자가 직접 만든 함수들
    strupr(string);
    fprintf(stdout, "to upper:\"%s\"\n", string);


    strlwr(string);
    fprintf(stdout, "to lower:\"%s\"\n", string);



    return 0;
}


// 대문자화
int strupr(char *str)
{
    int i=0;
    int len=0;
    len=strlen(str);


    for(i=0;i<len;i++)
    {
        *(str+i)=_toupper(*(str+i));
    }

    return i;
}



// 소문자화
int strlwr(char *str)
{
    int i=0;
    int len=0;
    len=strlen(str);


    for(i=0;i<len;i++)
    {
        *(str+i)=_tolower(*(str+i));
    }

    return i;
}
