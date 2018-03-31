#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;


class Phone {
  string name;
  string telnum;
  string address;

 public:
  Phone(string name="", string telnum="", string address=""){
    this->name = name;
    this->telnum = telnum;
    this->address = address;
  }

};


int main(int argc, char *argv[]){
  Phone girl("Ashley", "010-6655-1111", "hi");


  return 0;
}
