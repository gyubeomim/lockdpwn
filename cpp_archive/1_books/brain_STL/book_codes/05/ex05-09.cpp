#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void main( )
{
    stack<int, vector<int> > st; // vector 컨테이너를 이용한 stack 컨테이너 생성

    st.push( 10 ); // 데이터 추가(입력)
    st.push( 20 );
    st.push( 30 );

    cout << st.top() << endl; // top 데이터 출력
    st.pop(); // top 데이터 삭제
    cout << st.top() << endl;
    st.pop();
    cout << st.top() << endl;
    st.pop();

    if( st.empty() ) // 스택이 비었는지 확인
        cout << "stack이 데이터 없음" << endl;
}
