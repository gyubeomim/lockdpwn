#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct Person {
  int age;
  string name;
  int join;

  bool cmp(const Person &v) const {
    if(age < v.age)
      return true;
    else if(age == v.age)
      return join < v.join;
    else
      return false;
  }
};
