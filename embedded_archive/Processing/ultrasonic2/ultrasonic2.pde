/*
 	processing ==> 초음파센서로 거리를 읽어 레이더를 그려주는 코드2
 */
import processing.serial.*;

Serial myPort;

class Ball
{
  int life = 50;
  float x,y;

  public Ball(float cx,float cy, int rad, int distance)
  {
    float d = map(distance,0,100,0,width/2);
    float r = TWO_PI - map(rad,0,360,0,TWO_PI);
    x = cx + cos(r) * d;
    y = cy + sin(r) * d;
  }

  public void display()
  {
    ellipse(x,y,life,life);
  }

  public void update()
  {
    --life;
    if(life<0)
    {
      life = 0;
    }
  }

  public boolean isDead()
  {
    return life == 0;
  }


}

int rad = 0;
float cx,cy;
ArrayList<Ball> balls = new ArrayList<Ball>();

void updateBalls()
{
  for(int i = balls.size() -1 ; i> -1 ; i--)
  {
    balls.get(i).update();

    if (balls.get(i).isDead())
    {
      balls.remove(i);  
    }
  }
}

void displayBalls()
{
  for(int i = 0 ; i < balls.size() - 1 ; i++)
  {
    balls.get(i).display();
  }
}

void serialEvent(Serial p)
{
    String inString = p.readStringUntil('\n');

    if(inString != null)
    {
      if(inString.startsWith("r"))
      {
        String[] strings = inString.trim().replace("r","").split("d");
        
        if(strings.length > 1)
        {
          rad = Integer.parseInt(strings[0]);
          int distance = Integer.parseInt(strings[1]);
          if(distance != 0)
          {
            balls.add(new Ball(cx,cy,rad,distance));
          }
        }
      }
    }
}


void setup()
{
	size(400,400);
	cx = width/2;
	cy = height*2/3;
	noFill();
	
	println(Serial.list());
	myPort = new Serial(this,Serial.list()[0],9600);
}

void draw()
{
	background(0);
	stroke(0,255,36);
	arc(cx,cy,width,height,PI,TWO_PI,CHORD);
	float r = TWO_PI - map(rad,0,360,0,TWO_PI);
	line(cx,cy,cx+cos(r)*width/2 , cy + sin(r) * height/2);
	updateBalls();
	displayBalls();
}
