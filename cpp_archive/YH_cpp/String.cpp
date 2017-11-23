/*
  열혈c++ string class 구현 코드
*/

#include "String.hpp"

using namespace std;


// 생성자
String::String()
{
  len = 0;
  str= NULL;
}


// 생성자2
String::String(const char* s)
{
  len = strlen(s) + 1;
  str = new char[len];
  strcpy(str, s);
}


// 생성자3
String::String(const String& s)
{
  len = s.len;
  str = new char[len];
  strcpy(str, s.str);
}


// 소멸자
String::~String()
{
  if(str != NULL)
  {
    delete []str;
  }
}


// = 연산자 오버로딩
String& String::operator=(const String& s)
{
  if(str!=NULL)
  {
    delete []str;
  }

  len = s.len;
  str= new char[len];
  strcpy(str, s.str);
  return *this;

}

// += 연산자 오버로딩
String& String::operator+=(const String& s)
{
  len += (s.len -1);
  char* tempstr = new char[len];

  strcpy(tempstr,str);
  strcat(tempstr, s.str);

  if(str != NULL)
  {
    delete []str;
  }

  str = tempstr;
  return *this;
}


// == 연산자 오버로딩
bool String::operator==(const String& s)
{
  return strcmp(str, s.str) ? false : true;
}



// + 연산자 오버로딩
String String::operator+ (const String& s)
{
  char* tempstr = new char[len + s.len -1];

  strcpy(tempstr, str);
  strcat(tempstr, s.str);


  String temp(tempstr);
  delete []tempstr;


  return temp;
}


// << 연산자 오버로딩
ostream& operator<<(ostream& os, const String& s)
{
  os<<s.str;
  return os;
}


// >> 연산자 오버로딩
istream& operator>>(istream& is, String& s)
{
  char str[100];
  is >> str;

  s = String(str);

  return is;
}



