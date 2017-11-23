//#pragma once
//#include "Collection.h"
//#include "MyGlobal.h"


class Zone
{
  Collection *collection;


public:

  Zone(void);
  ~Zone(void);

  void Run();

private:
  void Init();
  void Exit();

  // MyGlobal::KeyData SelectMenu();

  void AddMember();
  void DelMember();

  void SearchByNumber();
  void SearchByName();
  void SortByNumber();
  void SortByName();

  void ListAll();
  void DeleteAll();
};
