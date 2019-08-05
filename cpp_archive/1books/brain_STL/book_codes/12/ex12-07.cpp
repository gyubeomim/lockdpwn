#include <iostream>
#include <string>
using namespace std;

void main( )
{
    const char *sz="\"Be careful in Uncle Randy's new car\", "
        "my sister told them. \"Wipe your feet before you get in it. "
        "Don't mess anything up. Don't get it dirty.\" "
        "I listened to her, and thought, "
        "as only a bachelor uncle can So I made things easy. "
        "while my sister was outlining the rules, "
        "I slowly and deliberately opened a can of soda, turned it over, "
        "and poured it on the cloth seats in the back of the convertible.";
    string t("Randy");
    string s = sz;
    
    //s:string객체, sz:'\0'문자열, c:문자, off:시작위치, n:길이
    cout << s << endl << endl;
    cout <<"s.find(c): "<< s.find('I') << endl;
    cout <<"s.find(c,off): "<< s.find('I', 250)<< endl;
    cout <<"s.find(sz): "<< s.find("poured it")<< endl;
    cout <<"s.find(sz,off): "<< s.find("poured it", 0)<< endl;
    cout <<"s.find(sz,off,n): "<< s.find("I listened to her",0,1)<< endl;
    cout <<"s.find(c): "<< s.find(t,0)<< endl << endl;
    
    string::size_type pos= s.find("Not found");    
    cout << (int)pos <<" : " << (int)string::npos << endl;

    pos = s.rfind('I');
    if( string::npos != pos )
        cout <<"s.rfind(c): " << pos << endl;
}