#include "LedControl.h"                    //  라이브러리는 첨부하였습니다.
LedControl lc=LedControl(12,11,10,1);     // 핀들을 접속 (DIN 핀,CLK 핀, CS핀, 주소) 여기서 주소는 몇번째 모들인지를 의미합니다.

void setup()
{
  lc.shutdown(0,false);     // 절전모드를 끄고,
  lc.setIntensity(0,2);    // 밝기를 설정합니다(0~15까지 밝기 설정가능합니다)
  lc.clearDisplay(0);      // 화면을 정리합니다
}
void loop()
{
  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,true);      // LED가 켜지면서 밑에서부터 올라갑니다.
      delay(25);                      // 25만큼 지연
    }
  }

  for (int row=0; row<8; row++)
  {
    for (int col=0; col<8; col++)
    {
      lc.setLed(0,col,row,false);       // LED가 꺼지면서 밑에서부터 올라갑니다
      delay(25);                        //25만큼 지연
    }
  }
}

// 위 작동이 반복되면 올라가면서 켜지고, 그 다음 올라가면서 다 꺼지고 다시 켜지면서 올라가고
//꺼지면서 올라가고 하는 동작이 반복됩니다


