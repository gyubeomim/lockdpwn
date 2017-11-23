/*
 *	c++ ==> 코드그라운드, base 난이도의 부분배열 문제를 벡터로 풀어본 코드 
 *						  다른사람의 코드를 복사해서 공부했다
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) 
{
	setbuf(stdout, NULL);

	int T;
	int test_case;

	scanf("%d", &T);	
	for (test_case = 1; test_case <= T; test_case++) 
	{
		vector<int> v;
		v.clear();

		int n, s;
		cin >> n >> s;

		int a;
		for (int i = 0; i < n; i++)
		{
			cin >> a;
			v.push_back(a);
		}

		int count = 0;
		int sum = 0;
		vector<int> ans;

		for (int i = 0; i < n; i++)
		{
			sum = v.at(i) + sum;
			count++;

			while (sum >= s)
			{
				ans.push_back(count);
				sum = sum - v.at(i + 1 - count);
				count--;
			}
		}

		if (count == n)
		{
			ans.push_back(0);
		}

		printf("#testcase%d\n", test_case);
		sort(ans.begin(), ans.end());
		cout << ans.at(0) << endl;
	}

	return 0;	
}
