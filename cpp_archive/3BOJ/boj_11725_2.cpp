/*
 * #+DESCRIPTION:  백준 11725, 트리의 부모 찾기 문제를 푼 정답 코드
 * #+CATEGORY:     BFS
 * #+LEVEL:        -
 * #+FROM:         http://hellogohn.com/post_one230
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <vector>
#include <queue>

#define MAX_SIZE 10001

using namespace std;

int parent[MAX_SIZE] = {0};
vector<int> node[MAX_SIZE];
int total_num;

void bfs() {
  queue<pair<int, int>> bfs_queue;

  for(int i=0; i < node[1].size(); i++) {
    bfs_queue.push({1, node[1].at(i)});
  }

  while(bfs_queue.size()) {
    pair<int, int> sub_ = bfs_queue.front();
    bfs_queue.pop();

    parent[sub_.second] = sub_.first;

    for(int i=0; i<node[sub_.second].size(); i++) {
      if(parent[node[sub_.second].at(i)] == 0) {
        bfs_queue.push({sub_.second, node[sub_.second].at(i)});
      }
    }
  }
}

int main(int argc, char **argv) {
  cin >> total_num;

  for(int i=0; i<total_num-1 ; i++) {
    int sub_1, sub_2;
    cin >> sub_1 >> sub_2;

    node[sub_1].push_back(sub_2);
    node[sub_2].push_back(sub_1);
  }

  parent[1] = -1;
  bfs();

  cout << "--------------------------------" << endl;
  for(int i=2; i<=total_num; i++) {
    cout << parent[i] << endl;
  }

  return 0;
}
