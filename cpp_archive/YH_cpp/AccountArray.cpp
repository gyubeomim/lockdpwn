

#include <cstdlib>
#include "BankingCommonDecl.hpp"
#include "AccountArray.hpp"

using namespace std;


// 생성자 (len 기본값은 100)
BoundCheckAccountPtrArray::BoundCheckAccountPtrArray(int len)
    : arrlen(len)
{
  arr= new ACCOUNT_PTR[len];
}



// [] 연산자 오버로딩
ACCOUNT_PTR& BoundCheckAccountPtrArray::operator[](int idx)
{
  if(idx < 0 || idx >= arrlen)
  {
    cout << "Array index out of bound exception" << endl;
    exit(1);
  }

  return arr[idx];
}


// [] 연산자 오버로딩2
ACCOUNT_PTR BoundCheckAccountPtrArray::operator[] (int idx) const
{
  if(idx < 0 || idx >= arrlen)
  {
    cout << "Array index out of bound exception" << endl;
    exit(1);
  }

  return arr[idx];

}


// 현재 계좌갯수 출력
int BoundCheckAccountPtrArray::GetArrLen() const
{
  return arrlen;
}


// 소멸자
BoundCheckAccountPtrArray::~BoundCheckAccountPtrArray()
{
  delete []arr;
}
