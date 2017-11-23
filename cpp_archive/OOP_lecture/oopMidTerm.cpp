#include <iostream>
#include <string>
using namespace std;

// 객체지향 중간고사 문제 1
// 아래 코드의 출력 결과를 쓰시오
void power(int n[], int size){
	for(int i = 0; i < size ; i++){
		n[i] = n[i] * n[i];
	}
}

int main(int argc, const char *argv[]){
	int m[] = {1, 2, 3};
	power(m,3);

	for(int i = 0 ; i < 3 ; i++){
		cout << m[i] << ' ';
	}

	return 0;
}

// 객체지향 중간고사 문제 2
// 아래 코드의 출력 결과를 쓰시오
/*
int array[9] = {0,2,4,6,8,10,14,16,18};

int& f(int n){
  return array[n];
}

int main(int argc, char *argv[]){
  f(9) = 100;

  for(int i = 0 ; i < 10 ; i++){
    cout << array[i] << ' ';
  }

  return 0;
}
*/


// 객체지향 중간고사 문제 3
// 아래 코드의 출력 결과를 쓰시오
/*
int main(int argc, char *argv[]){
  string s("I Love");
  string a;
  a = s;
  a.append(" C++");

  cout << a << endl;

  a.erase(6,10);
  a.append(" You");

  cout << a << endl;

  int len = a.length();

  for(int i = 0 ; i < 3 ;  i++){
    string first = a.substr(0,1);
    string sub = a.substr(1, len - 1);
    a = sub + " " + first;
    cout << a << endl;
  }

  return 0;
}
*/

