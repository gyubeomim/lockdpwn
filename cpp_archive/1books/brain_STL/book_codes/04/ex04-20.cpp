#include <iostream>
#include <string>
using namespace std;

template <typename IterT, typename Func>
void For_each(IterT begin,IterT end, Func pf )
{
    while( begin != end )
    {
        pf( *begin++ ); 
    }
}
template <typename T>
struct PrintFunctor
{
    string sep; // 출력 구분자 정보
public:
    explicit PrintFunctor(const string& s=" "):sep(s) { }
    void operator()(T data) const
    {
        cout << data <<sep;
    }
};
void main( )
{
    int arr[5] = {10, 20, 30, 40, 50};
    For_each(arr, arr+5, PrintFunctor<int>()); 
    cout << endl;

    string sarr[3] = {"abc","ABCDE","Hello!"};
    For_each(sarr, sarr+3, PrintFunctor<string>("*\n"));
    cout << endl;
}

