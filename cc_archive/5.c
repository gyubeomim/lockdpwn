#include <stdio.h>
#include <ctype.h>
 
void Reverse(char s[]);
 
void main()
{
    char s[100] = { 0 };
    char c;
    int count = 0;
 
    printf("Please Enter a Sentence : ");
 
 
    // Enter를 입력할 때까지 문장을 입력해서 s에 저정합니다
    for (; (c = getchar()) != '\n';)  
    {
        s[count] = c;
        count++;
    }
    
 
    Reverse(s);   
 
    printf("Reversed Sentence is : %s\n", s);
 
}
void Power(int i)

void Reverse(char s[])
{
    char* p;
    char q[100] = { 0 };
    int count = 0;
    int count2 = 0;
 
    p = s;  // p 포인터는 문자열 (s)를 가르킵니다
    
 
    // 문자열 끝까지 count를 증가시킨 다음
    for (count = 0; p[count] != '\0';)
        count++;
    
 
 
    // count를 감소하면서  q에 문자열을 거꾸로 넣고
    for (count-- ; count >= 0; count--)
    {
        q[count2] = p[count];
        count2++;
    }
 
 
    // 최종적으로 s에 거꾸로 입력된 문자를 입력한다 
    for (count = 0; q[count] != '\0' ;count++)
        s[count] = q[count];
 
}
