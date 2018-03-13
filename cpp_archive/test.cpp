/*
 * c++ ==> 객체지향 p. 
 */
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

<<<<<<< HEAD



int main(int argc, const char *argv[]) {
		Phone girl, boy;
	
		cin >> girl >> boy;
		cout << girl << endl << boy << endl;
=======
int main(int argc, const char *argv[]){
  Phone girl, boy;
>>>>>>> c46d972e32e778b694cd19406715fcd77c2c9526


  cin >> girl >> boy;
  cout << girl << endl << boy << endl;



      return 0;
}
