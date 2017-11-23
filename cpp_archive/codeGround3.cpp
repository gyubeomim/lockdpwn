/*
 *	c++ ==> 코드그라운드, easy 난이도의 프로그래밍 경진대회 문제를 
 *						벡터와 알고리즘을 사용해 풀어본 코드
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(int argc, char** argv) 
{
	setbuf(stdout, NULL);

	vector<int> v;
	int TC;
	int test_case;
	int manNum;
	int count = 0;

	scanf("%d", &TC);	
	for (test_case = 1; test_case <= TC; test_case++) 
	{
		scanf("%d", &manNum);
		
		v.clear();
		v.resize(manNum);

		for (int i = 0; i < manNum; i++)
		{
			scanf("%d", &v[i]);
		}

		count = manNum;
		sort(v.begin(), v.end(), greater<int>());  // 오름차순으로 하려면 다음과 같이 해야한다
		
		for (int j = 1; j < manNum; j++)
		{
			if ((v[0] - v[manNum - j]) >= manNum)
			{
				count -= 1;
			}
		}
		
		printf("Case #%d\n", test_case);	
		printf("%d\n", count);
	}

	return 0;	
}
