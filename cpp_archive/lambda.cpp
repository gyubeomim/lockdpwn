/*
  c++ ==> lambda로 사칙연산을 해본 예제 코드
*/
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv){
    int a,b;
    cout << "Input : ";
    cin >> a >> b;

    vector<function<int(int,int)>> d;
    d.push_back([](int x, int y){
            return x+y;
        });
    d.push_back([](int x, int y){
            return x-y;
        });
    d.push_back([](int x, int y){
            return x*y;
        });
    d.push_back([](int x, int y){
            return x/y;
        });

    for(auto &f : d){
        cout << f(a,b) << '\n';
    }

    return 0;
}
