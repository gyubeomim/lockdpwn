#include "common.h"
#include "game.h"


int calcPercent(int win,int lose)
{
  int percent;
  int sum;

  if(win ==0 && lose ==0)
  {
    return 0;
  }
  
  sum = win + lose;

  percent = win*100/sum;


  return percent;
  
}
