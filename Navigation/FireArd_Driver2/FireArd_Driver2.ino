/*  Fire Fighting Robot Coding
 *  11/2/2016
 *  Code for robot with two motor drivers
 *  FiFi 3
 *  -------------------------------------------------------------
 *  NOTE: LOW = 0; HIGH = 1; PWM = 0~255 when using motor driver 2
 *  LOW is backwards, and HIGH is forward
 *  The IR sensors read higher numbers when the object, or wall, are closer. (The farther, the lower number it is,) 
 */
int x = 0;

//Pin Assignments
int E1 = 6; //Speed 1
int M1 = 7; //Direction 1
int E2 = 5; //Speed 2                         
int M2 = 4; //Direction 2
int E3 = 8; //Fan
int M3 = 9;

int ldist; // LEFT SENSOR READ
int fdist; // FRONT SENSOR READ
int rdist; // RIGHT SENSOR READ
int fsense; // FLAME SENSOR READ

boolean lClose;
boolean fClose;
boolean rClose;
boolean flameSensed;


void setup(){ 
  pinMode(M1, OUTPUT);           
  pinMode(M2, OUTPUT); 
  pinMode(M3, OUTPUT);   
  delay(500);                    //wait 3 seconds before starting. (prevents bot from moving before it is on the floor)
  Serial.begin(9600);            //19200 bits-per-second
  Serial.println("FIRE FIGHTING ROBOT ACTIVATED");
}

/***********************************************************************/
void loop() {
  lClose = false;
  fClose = false;
  rClose = false;
  flameSensed = false;
  
  readSensors();                                  //Read fire sensor and IR sensors.If fire is detected, sensedFire becomes true
  flameSensed = sensedFire();
  if (flameSensed == true){                         //senseFire is true, then the fan is on and the motors are off
    blow();
    Serial.println("flameSensed is true");
    Stop();
    delay(2000);
  } 
  else if (flameSensed == false){
    followRightWall();  
    delay(100);           
  }
  flameSensed = false;  

   delay(3000);
}
/***********************************************************************/

boolean sensedFire()
{
  if (fsense < 50)
  {
    Serial.println(" ");
    Serial.print("FIRE DETECTED");
    Serial.println(" ");
    return true;
  }
  else
    return false;
}

void readSensors()
{
  ldist = analogRead(1);
  fdist = analogRead(3);
  rdist = analogRead(2);
  fsense = analogRead(0);
            
  Serial.println();
  Serial.println("New Readings and Actions");
  Serial.print("Left"); Serial.print("       ");
  Serial.print("Front"); Serial.print("       ");  
  Serial.print("Right"); Serial.print("       ");
  Serial.print("Flame Sensor Reads"); Serial.print("       ");
  Serial.println();
  Serial.print(ldist); Serial.print("       ");
  Serial.print(fdist); Serial.print("          ");
  Serial.print(rdist); Serial.print("            ");
  Serial.print(fsense); Serial.print("          ");
  Serial.println();
  
  if (ldist > 370)
  {
    lClose = true;  
    Serial.print("LEFT is Close ");
    Serial.println(lClose);
  }
  
  if (fdist > 290)
  {
    fClose = true;
    Serial.print("FRONT is Close ");
    Serial.println(fClose);
  }

  if (rdist > 250)
  {
    rClose = true; 
    Serial.print("RIGHT is Close ");
    Serial.println(rClose);
  }
}


void blow()
{
  digitalWrite(M3,HIGH);   
  analogWrite(E3, 250);
  Serial.println("fanPin is on");
  delay(2000);
  //Maybe should turn off the fan at some point
}

//********************************************
//Defining Robot's Potential Actions as functions
//Stop, move forward, turn left, turn right
//Call different order of functions depending on the potential
//situations in the maze (3-way fork, left only, etc.)
//********************************************

void Stop()
  {
    digitalWrite(M1,LOW);   
    digitalWrite(M2,LOW);       
    analogWrite(E1, LOW);   //PWM Speed Control
    analogWrite(E2, LOW);   //PWM Speed Control 
  }

void goForward()
  {
    digitalWrite(M1,HIGH);   
    digitalWrite(M2,HIGH);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control
  }

void turnRight()  //90 DEGREES CLOCKWISE
  {
    digitalWrite(M1,LOW);   
    digitalWrite(M2,HIGH);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control 
    delay(400);    
  }

void turnLeft()  //90 DEGREES COUNTER-CLOCKWISE
  {
    digitalWrite(M1,HIGH);   
    digitalWrite(M2,LOW);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control 
    delay(400);    
  }

void goBackwards()
  {
    digitalWrite(M1,LOW);   
    digitalWrite(M2,LOW);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control
  }

/*
void tiltLeft()
{
  analogWrite(motor1Pin1, 100);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, 150);
  analogWrite(motor2Pin2, LOW);
}
*/  


// Right wall follow algorithm

void followRightWall()
{
  Serial.println("*****************runMotors*****************");
  //DEFAULT: GO FORWARD
  if ( rClose == 1 && fClose == 0 ) // if right is close and front is far, go forward
  {
    Serial.println(" ");
    Serial.print("GO FORWARD");
    Serial.println(" ");
    goForward();  
  }

  /*
  if ( lClose ==1 && fClose == 0 ) // if left is close and front is far, go forward
  {
    Serial.println(" ");
    Serial.print("GO FORWARD");
    Serial.println(" ");
    goForward();  
  }

  //STOP
  else if ( fClose && rClose ) // but if front left right are too ALL close, stop
  {
    Serial.println(" ");
    Serial.print("STOP");
    Serial.println(" ");
    Stop();
  }
   */
      
  //TURN RIGHT
  else if (rClose == 0) // if the right dist is far, then turn right 
  {
    Serial.println(" ");
    Serial.println("TURN RIGHT");
    Serial.println(" ");
    turnRight();
    goForward();
  }

  //TURN LEFT
  else if ( lClose == 0 && rClose == 1 && fClose == 1 )
  {
    Serial.println(" ");
    Serial.println("TURN LEFT");
    Serial.println("");
    turnLeft();
    goForward();
  }

  else
  {
    Stop();
  }
}
