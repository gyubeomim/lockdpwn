/*
	c++ stl p288 multimap ==> lower_bound(3), upper_bound(3), equal_range(3)을 사용해 
							  multimap에서 중복된 값을 찾는 예제코드
*/
#include <iostream>
#include <map>

using namespace std;

int main()
{

	multimap<int, int> mm;


	mm.insert(pair<int, int>(5, 100));
	mm.insert(pair<int, int>(3, 100));
	mm.insert(pair<int, int>(8, 30));
	mm.insert(pair<int, int>(3, 40));
	mm.insert(pair<int, int>(1, 70));
	mm.insert(pair<int, int>(7, 100));
	mm.insert(pair<int, int>(8, 50));




	// key : 3 인 원소를 찾는 첫번째 방법 (lower_bound(3), upper_bound(3)를 사용합니다)
	multimap<int, int>::iterator lower_iter;
	multimap<int, int>::iterator upper_iter;


	lower_iter = mm.lower_bound(3);
	upper_iter = mm.upper_bound(3);



	cout << "구간 [lower_iter, upper_iter)의 순차열: ";
	
	multimap<int, int>::iterator iter;

	
	for (iter = lower_iter; iter != upper_iter; iter++)
	{
		cout << "(" << iter->first << ',' << iter->second << ")";
	}
	cout << endl;




	// key : 3인 원소를 찾는 두번째 방법 equal_range(3)을 사용합니다
	pair < multimap<int, int>::iterator, multimap<int, int>::iterator> iter_pair;
	iter_pair = mm.equal_range(3);


	cout << "구간 [iter_pair.first, iterpair second)의 순차열: ";
	for (iter = iter_pair.first; iter != iter_pair.second; iter++)
	{
		cout << "(" << iter->first << ',' << iter->second << ")";
	}
	cout << endl;

	
	return 0;
}






















