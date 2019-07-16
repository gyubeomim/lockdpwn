#include <iostream>
#include "zone.h"

using namespace std;

//번호로 검색 시에 사용할 클래스 정의
class SearchByNumFun  :public Search
{
  int num;
 public:
  SearchByNumFun(int _num){num = _num;}
  virtual bool operator()(Member *mem)
  {
    return mem->GetNum() == num;
  }
};


//이름으로 검색 시에 사용할 클래스 정의
class SearchByNameFun  :public Search
{
  string name;
 public:
  SearchByNameFuna(string _name){name = _name;}
  virtual bool operator()(Member *mem)
  {
    return mem->GetName() == name;
  }
};


//번호 순으로 정렬 시에 내부 멤버를 비교하기 위해 제공하는 클래스 정의
class CompareByNumFun  :public Compare
{
 public:
  virtual int operator()(Member *mem1,Member *mem2)
  {
    return mem1->GetNum() - mem2->GetNum();
  }
};



//이름 순으로 정렬 시에 내부 멤버를 비교하기 위해 제공하는 클래스 정의
class CompareByNameFun
    :public Compare
{
 public:
  virtual int operator()(Member *mem1,Member *mem2)
  {
    string n1 = mem1->GetName();
    string n2 = mem2->GetName();
    return strcmp(n1.c_str(),n2.c_str());
  }
};



//전체 회원의 정보를 순차적으로 보여주기 위해 내부 멤버를 보여주기 위해 제공하는 클래스 정의
class ViewMember
    :public DoSomething
{
 public:
  virtual void operator()(Member *mem)
  {
    cout<<mem;
  }
};



//전체 회원을 해제화 하기 위해 내부 멤버를 해제하기 위해 제공하는 클래스 정의
class DeleteMember
    :public DoSomething
{
 public:
  virtual void operator()(Member *mem)
  {
    delete mem;
  }
};


Zone::Zone(void)
{
  Init();
}

Zone::~Zone(void)
{
  Exit();
}

void Zone::Init()
{
  cout<<"최대 관리할 회원 수를 입력하세요"<<endl;
  int max_member = MyGlobal::GetNum();
  collection = new Collection(max_member);
}

void Zone::Exit()
{
  DeleteAll();
  delete collection;
}

void Zone::DeleteAll()
{
  //회원 개체를 소멸하기 위한 함수 개체
  DeleteMember dm;
  //collection 개체의 ListView에서 dm 함수 개체를 통해 순차적으로 모든 회원을 소멸시킴
  collection->ListAll(dm);
  //void Zone::ListAll()의 구현과 비교해 보세요.
}

void Zone::Run()
{
  MyGlobal::KeyData key;
  while((key = SelectMenu())!=MyGlobal::ESC)
  {
    switch(key)
    {
      case MyGlobal::F1: AddMember(); break;
      case MyGlobal::F2: DelMember(); break;
      case MyGlobal::F3: SearchByNumber(); break;
      case MyGlobal::F4: SearchByName(); break;
      case MyGlobal::F5: SortByNumber(); break;
      case MyGlobal::F6: SortByName(); break;
      case MyGlobal::F7: ListAll(); break;
      default: cout<<"잘못된 메뉴를 선택하였습니다."<<endl; break;
    }
    cout<<"아무키나 누르세요"<<endl;
    MyGlobal::GetKey();
  }
}

MyGlobal::KeyData Zone::SelectMenu()
{
  system("cls");
  cout<<"[F1]: 회원 추가 [F2]: 회원 삭제"<<endl;
  cout<<"[F3]: 번호로 회원 검색[F4]: 이름으로 회원 검색"<<endl;
  cout<<"[F5]: 번호순으로 정렬[F6]: 이름순으로 정렬"<<endl;
  cout<<"[F7]: 전체 보기"<<endl;
  cout<<"[ESC]: 프로그램 종료"<<endl;
  return MyGlobal::GetKey();
}

void Zone::AddMember()
{
  cout<<"회원 추가 기능입니다."<<endl;
  if(collection->IsFull())
  {
    cout<<"더 이상 회원을 추가할 수 없습니다."<<endl;
    return;
  }

  cout<<"추가할 회원의 번호를 입력하세요"<<endl;
  int num = MyGlobal::GetNum();

  //번호로 보관된 회원과 비교하기 위한 함수 개체 생성
  SearchByNumFun sbn(num);
  //collection의 FindMember에서 함수 개체를 통해 원하는 회원을 검색해 줌
  if(collection->FindMember(sbn))
  {
    cout<<"이미 존재하는 회원 번호입니다."<<endl;
    return;
  }

  cout<<num<<"번 회원의 이름을 입력하세요"<<endl;
  string name = MyGlobal::GetStr();

  if(collection->Push(new Member(num,name)))
  {
    cout<<"정상적으로 추가하였습니다."<<endl;
  }
  else
  {
    cout<<"내부적으로 오류가 발생하였습니다."<<endl;
  }
}

void Zone::DelMember()
{
  cout<<"회원 삭제 기능입니다."<<endl;
  int count = collection->GetCount();
  if(count == 0)
  {
    cout<<"보관된 회원이 없습니다."<<endl;
    return;
  }

  cout<<"삭제할 회원 번호를 입력하세요"<<endl;
  int num = MyGlobal::GetNum();
  //번호로 보관된 회원과 비교하기 위한 함수 개체 생성
  SearchByNumFun sbn(num);
  //collection의 GetMember에서 함수 개체를 통해 원하는 회원을 가져옮
  Member *mem = collection->GetMember(sbn);
  if(mem == 0)
  {
    cout<<"잘못된 번호를 입력하였습니다."<<endl;
    return;
  }

  cout<<mem<<endl;
  cout<<"회원을 삭제하겠습니다."<<endl;
  delete mem;

}



void Zone::SearchByNumber()
{
  cout<<"번호로 회원 검색 기능입니다."<<endl;
  int count = collection->GetCount();
  if(count == 0)
  {
    cout<<"보관된 회원이 없습니다."<<endl;return;
  }
  cout<<"검색할 회원 번호를 입력하세요"<<1<<"~"<<count<<endl;
  int num = MyGlobal::GetNum();
  SearchByNumFun sbn(num);
  Member *mem = collection->FindMember(sbn);
  if(mem == 0)
  {
    cout<<"잘못된 번호를 입력하였습니다."<<endl;return;
  }
  cout<<mem<<endl;
}
void Zone::SearchByName()
{
  cout<<"이름으로 회원 검색 기능입니다."<<endl;
  int count = collection->GetCount();
  if(count == 0)
  {
    cout<<"보관된 회원이없습니다."<<endl;return;
  }
  cout<<"검색할 회원 이름을 입력하세요"<<endl;
  string name = MyGlobal::GetStr();
  SearchByNameFun sbn(name);
  Member *mem = collection->FindMember(sbn);
  if(mem == 0)
  {
    cout<<"존재하지 않는 회원 이름 입니다."<<endl;return;
  }
  cout<<mem<<endl;
}

void Zone::SortByNumber()
{
  //번호 순으로 정렬에 필요한 회원 번호로 비교하는 함수 개체 생성
  CompareByNumFun cn;
  //colletion의 Sort 메서드에서는 전달받은 함수 개체를 이용하여 정렬
  collection->Sort(cn);
  ListAll();
}
void Zone::SortByName()
{
  //이름 순으로 정렬에 필요한 회원 번호로 비교하는 함수 개체 생성
  CompareByNameFun cn;
  //colletion의 Sort 메서드에서는 전달받은 함수 개체를 이용하여 정렬
  collection->Sort(cn);
  ListAll();
}
void Zone::ListAll()
{
  //회원 정보를 보여주기 위한 함수 개체 생성
  ViewMember vm;
  //collection의 ListAll에서는 vm을 이용하여 회원들의 정보를 보여줌
  collection->ListAll(vm);
}
