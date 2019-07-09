#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int v,max_dist,end_node;
int visited[100001] = {0};
vector<pair<int,int>> tree[100001];

void dfs(int now, int dist) {
  visited[now] = true;

	if(max_dist < dist) {
		max_dist = dist;
		end_node = now;
	}

  for (int i = 0; i < tree[now].size(); i++) {
    if (visited[tree[now][i].first] == false) {
      dfs(tree[now][i].first, dist + tree[now][i].second);
    }
  }
}

int main() {
  cin >> v;

  for (int i = 0; i < v; i++) {
		int root,node,dist;
		scanf("%d", &root);

		while(true){
			scanf("%d",&node);
			if(node==-1) break;
			scanf("%d",&dist);
			tree[root].push_back(make_pair(node,dist));
		}
  }

	dfs(1,0);
	max_dist=0;
	memset(visited,0,sizeof(visited));
	dfs(end_node,0);
  cout << max_dist << '\n';

  return 0;
}
