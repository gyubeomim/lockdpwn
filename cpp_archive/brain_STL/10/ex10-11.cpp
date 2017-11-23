#include <iostream>
#include <vector>
#include <list>
#include <iterator>
using namespace std;

void main() 
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    list<int> lt;
    lt.push_back(10);
    lt.push_back(20);
    lt.push_back(30);

    vector<int>::iterator viter(v.begin());
    list<int>::iterator liter(lt.begin());
    
    cout <<"viter: " <<*viter << endl; 
    cout <<"liter: " <<*liter << endl; 

    advance(viter, 2); // viter += 2
    advance(liter, 2);
    cout <<"viter: " <<*viter << endl; 
    cout <<"liter: " <<*liter << endl; 

    advance(viter, -2); // viter -= 2
    advance(liter, -2);
    cout <<"viter: " <<*viter << endl; 
    cout <<"liter: " <<*liter << endl; 
 }