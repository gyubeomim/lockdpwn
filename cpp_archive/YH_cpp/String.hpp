
#ifndef __STRING_H__
#define __STRING_H__

#include "BankingCommonDecl.hpp"


// string 클래스를 작게나마 구현해본 String 클래스
class String
{
 private:

  int len;
  char *str;




 public:

  // 생성자
  String();
  String(const char* s);
  String(const String& s);


  // 소멸자
  ~String();



  // 연산자 오버로딩
  String& operator=(const String& s);
  String& operator+=(const String& s);
  bool operator==(const String& s);
  String operator+ (const String& s);



  // 친구함수들 선언
  friend ostream& operator<<(ostream& os, const String& s);
  friend istream& operator>>(istream& is, String& s);

};

#endif
