#include "stdafx.h"
#include <iostream>
#include "CString.h"

using namespace std;

class Member
{
 private:
  CString m_Name;
  CString m_Addr;
  CString m_TelNo;

 public:
  Member(CString Name,CString Addr,CString TelNo)
  {
    m_Name = Name;
    m_Addr = Addr;
    m_TelNo = TelNo;
  }
  Member()
  {
  }
  friend ostream& operator << (ostream& o,const Member & rhs);

};

template <class T>
class Array
{
 private:
  T * m_pData;
  int	  m_iLength;

 public:
  Array(int x = 10);
  Array(const Array & rhs);
  Array & operator =(const Array & rhs);
  T & operator [](int x);
  T operator [](int x) const;
  ~Array();
  int GetLength();

};

template <class T>
Array<T>::Array(int x)
{
  cout << "Array<T>::Array(int x)" << endl;
  m_pData = new T[x];
  m_iLength = x;
  for(int i = 0;i < m_iLength;i++)
  {
    m_pData[i] = 0;
  }
}

Array<Member>::Array(int x)
{
  cout << "Array<Member>::Array(int x)" << endl;
  m_pData = new Member[x];
  m_iLength = x;
}

template <class T>
Array<T>::Array(const Array<T> & rhs)
{
  m_pData = new T[rhs.m_iLength];
  m_iLength = rhs.m_iLength;
  for(int i = 0;i < m_iLength;i++)
  {
    m_pData[i] = rhs.m_pData[i];
  }
}
template <class T>
Array<T> & Array<T>::operator =(const Array<T> & rhs)
{
  if (this == &rhs)
    return *this;
  delete [] m_pData;

  m_pData = new T[rhs.m_iLength];
  m_iLength = rhs.m_iLength;
  for(int i = 0;i < m_iLength;i++)
  {
    m_pData[i] = rhs.m_pData[i];
  }
  return *this;
}
template <class T>
T & Array<T>::operator [](int x)
{
  if (x >= m_iLength)
    return m_pData[m_iLength-1];
  else
    return m_pData[x];
}
template <class T>
T Array<T>::operator [](int x) const
{
  if (x >= m_iLength)
    return m_pData[m_iLength-1];
  else
    return m_pData[x];
}
template <class T>
Array<T>::~Array()
{
  delete [] m_pData;
}
template <class T>
int Array<T>::GetLength()
{
  return m_iLength;
}


ostream & operator << (ostream & o,const Member & rhs)
{
  o << "Name : " << rhs.m_Name << " Addr : " <<
      rhs.m_Addr << " TelNo : " << rhs.m_TelNo;
  return o;
}

template <class T>
class SubClass : public Array<T>
{
	
};

template <class T1,class T2>
class MyTestClass
{
 private:
  T1 m_Data1;
  T2 m_Data2;

 public:
  MyTestClass(T1 x,T2 y)
  {
    m_Data1 = x;
    m_Data2 = y;
  }
  void DispData()
  {
    cout << "m_Data1 -> " << m_Data1 << " m_Data2 => "
         << m_Data2 << endl;
  }

};

template <class T>
ostream & operator << (ostream & o,Array<T> & rhs)
{
  for(int i = 0;i < rhs.GetLength();i++)
  {
    o << rhs[i];
  }
  return o;
}

int main()
{
  int x = 1;
  Member m("È«±æµ¿","¼­¿ï","123-1234");
  Array<Member> MemberArray;

  MyTestClass<Member,Array<Member> > Sample(m,MemberArray);
  Sample.DispData();

}
