/*
	processing ==> 디지털제어 텀프로젝트
								 DCMotor의 각속도값을 읽어서 그래프로 변환해주는 코드
*/
import processing.serial.*;
 
long val = 0 ;
int xPos = 1 ;
Serial port ;

//Variables to draw a continuous line.
int lastxPos=1;
int lastheight=0; 
 
void setup()
{
	size(1500, 500) ;
	//  String portName = Serial.list()[3] ;
	port = new Serial(this, "COM3", 9600) ;
	// port = new Serial(this, portName, 9600) ;
	background(0) ;
	frameRate(30);
	drawGraphLabel();
}

void draw()
{
	while (port.available() >= 2) 
	{
		// 시리얼 포트로부터 데이터(Byte)를 읽습니다.
		String inString = port.readStringUntil('\n');
		println(inString);
		if (inString != null) 
		{
			inString = trim(inString);                // trim off whitespaces.
			float inByte = float(inString);           // convert to a number.
			inByte = map(inByte, 0, 20, 0, height); 
      //map to the screen height.
     
			//Drawing a line from Last inByte to the new one.
			stroke(0,255,0);     //stroke color
			strokeWeight(2);        //stroke wider
			line(lastxPos, lastheight, xPos, height - inByte); 
			lastxPos= xPos;
			lastheight= int(height-inByte);

			// at the edge of the window, go back to the beginning:
			if (xPos >= width) 
			{
				xPos = 0;
				lastxPos= 0;
				background(0);  //Clear the screen.
				drawGraphLabel();
			} 
			else 
			{
				// increment the horizontal position:
				// Ts = 0.1초인 경우 30으로 설정하고 
				// 아래에서 x축을 += 60으로 설정해주면 5칸에 1초가 된다
				xPos += 30;
			}
		}  
	}
}

// 그래프 x,y축을 그리는 함수
void drawGraphLabel() 
{
	// x축 : 시간을 설정하는 함수
	for(int i = 0; i <= width ; i += 60)
	{
		fill(255,255,0);
		text(i/300.0, i, height-15);
		stroke(155);
		line(i, height, i, 0);
	}

	// y축 : Angular Vel 각속도를 나타내는 함수
	for(int j =0 ; j < height; j += 25)
	{
		fill(255,255,0);
		// 아래 값에 따라 y축의 크기가 달라진다
		text(20-j/(height/20),0,j);
		textSize(15);
		stroke(55);
		line(0,j,width,j);
	}
}
