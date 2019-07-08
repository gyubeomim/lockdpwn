#include <iostream>
#include <vector>

using namespace std;

int N;
vector<pair<char,char>> v[26];

void preOrder(char root) {
	char left=v[root-'A'].front().first;
	char right=v[root-'A'].front().second;

	printf("%c",root);
	if(left!='.') preOrder(left);
	if(right!='.') preOrder(right);
}

void inOrder(char root) {
	char left=v[root-'A'].front().first;
	char right=v[root-'A'].front().second;

	if(left!='.') inOrder(left);
	printf("%c",root);
	if(right!='.') inOrder(right);
}

void postOrder(char root) {
	char left=v[root-'A'].front().first;
	char right=v[root-'A'].front().second;

	if(left!='.') postOrder(left);
	if(right!='.') postOrder(right);
	printf("%c",root);
}

int main() {
	cin >> N;

	for(int i=0;i<N;i++){
		char n,l,r;
		scanf(" %c %c %c", &n,&l,&r); // " %c..." 같이 첫 칸을 띄워주는게 포인트
		v[n-'A'].push_back({l,r});
	}

	preOrder('A');
	cout << '\n';
	inOrder('A');
	cout << '\n';
	postOrder('A');
	cout << '\n';

  return 0;
}
