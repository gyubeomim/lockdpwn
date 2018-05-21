/*
  c++ ==> 백준 5052, 전화번호 목록 문제를 푼 정답 코드

  TRIE (유사 tree 구조) 라는 구조체를 선언해서 문제를 풀었다

  code from [http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220576143081&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList]
*/
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

struct Trie {
  Trie* go[10];
  // output:  이 노드에서 끝나는 전화번호가 있으면 true
  // goexist: 이 노드에서 이어지는 전화번호가 있으면 true
  bool output, goexist;

  Trie() {
    memset(go, 0, sizeof(go));
    output = goexist = false;
  }
  ~Trie() {
    for(int i=0; i<10; i++)
      if(go[i]) delete go[i];
  }

  /*
    문자열 key를 현재 노드에 삽입하는 동시에
    이 삽입 과정에서 일관성이 깨졌는지를 리턴하는 함수
  */
  bool insert(const char* key) {
    if(*key == '\0') {
      output = true;
      // 이 노드에서 이어지는 다른 전화번호가 있으면 일관성 깨짐
      return goexist;
    }

    int next = *key - '0';
    if(!go[next])
      go[next] = new Trie;

    goexist = true;
    // 이 노드에서 끝나는 다른 번호가 있으면 일관성 깨짐
    return output || go[next]->insert(key+1);
  }
};

int main() {
  int T;
  cin >> T;

  for(int t=0; t<T; t++) {
    int N;
    cin >> N;
    Trie *root = new Trie;
    bool result = true;

    for(int i=0; i<N; i++) {
      char tel[11];
      scanf("%s", tel);
      if(result && root->insert(tel))
        result = false;
    }
    puts(result ? "YES" : "NO");
    delete root;
  }

  return 0;
}
