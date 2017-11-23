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
	size(600, 200) ;
	//  String portName = Serial.list()[3] ;
	port = new Serial(this, "COM3", 9600) ;
	// port = new Serial(this, portName, 9600) ;
	background(0) ;
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
			} 
			else 
			{
				// increment the horizontal position:
				xPos++;
			}
		}  
	}
}
