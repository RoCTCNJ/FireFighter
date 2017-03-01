
// NOTE: This code is not even close to functional, we ran into so many issues we didnt have time to do any actual coding

int front, left, right, flameCheck;
int rightTurns=0;
int leftTurns=0;
//the ports for each feel/sensor

int E1 = 6; //speed of left 
int E2 = 5; // speed of right
int M1 = 7; // movement of left
int M2 = 4; // movement of right
int E3 = 35; // fan speed
int M3 = 34; // fan movement

//purpose: start the methods and set the fan as an output
void setup()
{
 Serial.begin(9600); 
 pinMode(E1, OUTPUT);
 pinMode(E2, OUTPUT);
 pinMode(E3, OUTPUT);
 pinMode(M1, OUTPUT);
 pinMode(M2, OUTPUT);
 pinMode(M3, OUTPUT);
}

//purpose: sense nearness to walls and fire
//allow for fan to blow and movement to occur
void think(int dir)
{
  Serial.println("Thinking...");
    stopTurning();
  if(dir == 1)
    turnRight();
  if(dir==-1)
    turnLeft();
  delay(1000);
}
void loop()
{
front = analogRead(1);
right = analogRead(2); 
left = analogRead(0);
flameCheck = !(digitalRead(50));
Serial.println(String(left) + " " + String(front) + " " + String(right));
if (flameCheck)
{
  digitalWrite(E3, HIGH);
  digitalWrite(M3, HIGH);
  //delay (1000); // wait one second
  digitalWrite(E3, LOW);
}// end flamecheck if
//checks proximity to flame

//this will check closeness to walls
//and move it depending closeness to walls

if (front > 400 && right > 400 && left > 400)
{
  //turn around;

}
else if(left > 400 && front > 400)
{
  //turn right
  think(1);
}
else if(right > 400 && front > 400)
{
  //turn left
  think(-1);
}
else if(right > 400 && left > 400)
{
  //move forward
  goForward();
}
else if (front > 400)
    {
      //turn right
      think(1);
    }
else if (right > 400 || left > 400)
    {
      //forward
      goForward();
    }
else
{
  //move forward
  goForward();
}

 delay(100); //Delay the output by 1s (500ms) 
}


void stopTurning()
  {
    digitalWrite(M1,LOW);   
    digitalWrite(M2,LOW);       
    analogWrite(E1, LOW);   //PWM Speed Control
    analogWrite(E2, LOW);   //PWM Speed Control
    //stack.push('*'); 
  }

void goForward()
  {

    digitalWrite(M1,HIGH);   
    digitalWrite(M2,HIGH);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control
    //stack.push('F'); 
  }

void turnRight()  //90 DEGREES CLOCKWISE
  {
        Serial.println("Right");
    digitalWrite(M1,LOW);   
    digitalWrite(M2,HIGH);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control 
    //stack.push('R');   
    rightTurns++;  
  }

void turnLeft()  //90 DEGREES COUNTER-CLOCKWISE
  {
            Serial.println("Left");
    digitalWrite(M1,HIGH);   
    digitalWrite(M2,LOW);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control 
    //stack.push('L');    
    Serial.println("Turning left"); 
    leftTurns++;
  }

void goBackwards()
  {
    digitalWrite(M1,LOW);   
    digitalWrite(M2,LOW);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control
    //stack.push('B'); 
  }

