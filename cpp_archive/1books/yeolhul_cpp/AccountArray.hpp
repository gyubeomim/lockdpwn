
#ifndef __ACCOUNT_ARRAY_H__
#define __ACCOUNT_ARRAY_H__

#include "Account.hpp"

typedef Account* ACCOUNT_PTR;



class BoundCheckAccountPtrArray
{
 private:

  ACCOUNT_PTR *arr;
  int arrlen;

  BoundCheckAccountPtrArray(const BoundCheckAccountPtrArray& arr)
  {}
  BoundCheckAccountPtrArray& operator=(const BoundCheckAccountPtrArray& arr)
  {}



 public:

  BoundCheckAccountPtrArray(int len = 100);

  ACCOUNT_PTR& operator[](int idx);

  ACCOUNT_PTR operator[] (int idx) const;

  int GetArrLen() const;

  ~BoundCheckAccountPtrArray();

};
#endif
