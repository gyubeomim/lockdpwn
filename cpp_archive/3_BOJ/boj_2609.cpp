/*
 * #+DESCRIPTION:  백준 2609, 최대공약수와 최소공배수
 * #+CATEGORY:     수학
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 수학1
 * #+DATE:         2018-06-12-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

int gcd(int x, int y){
    if(y==0) return x;
    else return gcd(y, x%y);
}

int main(){
    int a,b;
    cin >> a >> b;
    int g = gcd(a,b);

    cout << g << endl << a*b/g << endl;

}
