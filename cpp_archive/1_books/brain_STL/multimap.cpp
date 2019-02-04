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



	multimap<int, int>::iterator iter;

	for (iter = mm.begin(); iter != mm.end(); iter++)
	{
		cout << "(" << iter->first << ',' << iter->second << ")" << " ";
	}
	cout << endl;




	// count(3)을 사용합니다
	cout << "key 3 원소의 갯수는 : " << mm.count(3) << endl;

		
	// find(3)을 사용합니다
	iter = mm.find(3);
	if (iter != mm.end())
	{
		cout << "첫번째 key 3에 매핑된 value는 : " << iter->second << endl;
	}
	cout << endl;


	return 0;
}






















