#include <iostream>
#include <vector>

using namespace std;

int N;
bool visited[100001];
int parent[100001] = {0};
vector<int> v[100001];

void dfs(int now) {
  visited[now] = true;

  for (int i = 0; i < v[now].size(); i++) {
    int next = v[now][i];
    if (!visited[next]) {
      parent[next] = now;
      dfs(next);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> N;

  for (int i = 0; i < N - 1; i++) {
    int x, y;
    cin >> x >> y;

		v[x].push_back(y);
		v[y].push_back(x);
  }

  dfs(1);

  for (int i = 2; i <= N; i++) {
    if (parent[i])
      cout << parent[i] << '\n';
  }

  return 0;
}
