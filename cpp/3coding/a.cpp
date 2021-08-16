#include <bits/stdc++.h>



using namespace std;



// case: 1,2,4,8,  3,5,6,7,9,10,11,12,14,15
//       W N E S   WN(3), WE(5), NE(6), WNE(7), WS(9), NS(10), WNS(11), ES(12), NES(14), WNES(15)

enum Dir { W = 1, N = 2, E = 4, S = 8, WN = 3, WE = 5, NE = 6, WNE = 7, WS = 9, NS = 10, WNS = 11, ES = 12, NES = 14, WNES = 15};








class Map {

  Map(int n, int m)
      n_(n), m_(m)
  {

    wall_ = new Wall[m][n];


    visit_ = new bool[m][n];

  }






  void SetWall() {

    for(int i=0; i<m; i++) {
      for(int j=0; j<n; j++ ) {
        int status;

        cin >> status;




//       W N E S   WN(3), WE(5), NE(6), WNE(7), WS(9), NS(10), WNS(11), ES(12), NES(14), WNES(15)
        switch(status) {
          case W:
            wall_[i][j].block_[W] = true;

            if(IsValid(i, j-1))
              wall_[i][j-1].block_[E] = true;


            break;

          case N:
            wall_[i][j].block_[N] = true;

            if(IsValid(i-1, j))
              wall_[i-1][j].block_[S] = true;

            break;

          case E:
            wall_[i][j].block_[E] = true;


            if(IsValid(i, j+1))
              wall_[i][j+1].block_[W] = true;

            break;

          case S:
            wall_[i][j].block_[S] = true;


            if(IsValid(i+1, j))
              wall_[i+1][j].block_[N] = true;
            break;

          case WN:
            wall_[i][j].block_[W] = true;
            wall_[i][j].block_[N] = true;


            if(IsValid(i, j-1))
              wall_[i][j-1].block_[E] = true;
            if(IsValid(i-1, j))
              wall_[i-1][j].block_[S] = true;
            break;

          case WE:
            wall_[i][j].block_[W] = true;
            wall_[i][j].block_[E] = true;


            if(IsValid(i, j-1))
              wall_[i][j-1].block_[E] = true;
            if(IsValid(i, j+1))
              wall_[i][j+1].block_[W] = true;
            break;

          case NE:
            wall_[i][j].block_[N] = true;
            wall_[i][j].block_[E] = true;


            if(IsValid(i-1, j))
              wall_[i-1][j].block_[S] = true;
            if(IsValid(i, j+1))
              wall_[i][j+1].block_[W] = true;
            break;

          case WNE:
            wall_[i][j].block_[W] = true;
            wall_[i][j].block_[N] = true;
            wall_[i][j].block_[E] = true;


            if(IsValid(i, j-1))
              wall_[i][j-1].block_[E] = true;
            if(IsValid(i-1, j))
              wall_[i-1][j].block_[S] = true;
            if(IsValid(i, j+1))
              wall_[i][j+1].block_[W] = true;
            break;

          case WS:
            wall_[i][j].block_[W] = true;
            wall_[i][j].block_[S] = true;


            if(IsValid(i, j-1))
              wall_[i][j-1].block_[E] = true;
            if(IsValid(i+1, j))
              wall_[i+1][j].block_[N] = true;
            break;

          case NS:
            wall_[i][j].block_[N] = true;
            wall_[i][j].block_[S] = true;


            if(IsValid(i-1, j))
              wall_[i-1][j].block_[S] = true;
            if(IsValid(i+1, j))
              wall_[i+1][j].block_[N] = true;
            break;

          case WNS:
            wall_[i][j].block_[W] = true;
            wall_[i][j].block_[N] = true;
            wall_[i][j].block_[S] = true;


            if(IsValid(i, j-1))
              wall_[i][j-1].block_[E] = true;
            if(IsValid(i-1, j))
              wall_[i-1][j].block_[S] = true;
            if(IsValid(i+1, j))
              wall_[i+1][j].block_[N] = true;
            break;

          case ES:
            wall_[i][j].block_[E] = true;
            wall_[i][j].block_[S] = true;


            if(IsValid(i, j+1))
              wall_[i][j+1].block_[W] = true;
            if(IsValid(i+1, j))
              wall_[i+1][j].block_[N] = true;
            break;

          case NES:
            wall_[i][j].block_[N] = true;
            wall_[i][j].block_[E] = true;
            wall_[i][j].block_[S] = true;


            if(IsValid(i-1, j))
              wall_[i-1][j].block_[S] = true;
            if(IsValid(i, j+1))
              wall_[i][j+1].block_[W] = true;
            if(IsValid(i+1, j))
              wall_[i+1][j].block_[N] = true;
            break;

          case WNES:
            wall_[i][j].block_[W] = true;
            wall_[i][j].block_[N] = true;
            wall_[i][j].block_[E] = true;
            wall_[i][j].block_[S] = true;


            if(IsValid(i, j-1))
              wall_[i][j-1].block_[E] = true;
            if(IsValid(i-1, j))
              wall_[i-1][j].block_[S] = true;
            if(IsValid(i, j+1))
              wall_[i][j+1].block_[W] = true;
            if(IsValid(i+1, j))
              wall_[i+1][j].block_[N] = true;
            break;

        }
      }
    }
  }




  bool IsValid(int a, int b) {
    if(a < 0 || b >= n_ || b < 0 || b >= m_)
      return true;

    return false;
  }






  void BFS() {
    queue<int> Q_;
    Q_.push(0,0);


   
  }




 private:
  Wall **wall_;

  bool **visit_;



  int room_num_;
  int max_area_;



  const int n_;
  const int m_;

};







class Wall {
 public:

  Wall()
      :block_[](false)
  {}


  bool block_[4];
  // 1: W
  // 2: N
  // 4: E
  // 8: S


};










int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);


  int n, m;
  cin >> n >> m;




  Map m(n,m);
  m.SetWall();
  m.BFS();






  return 0;
}
