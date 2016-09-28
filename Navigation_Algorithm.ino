// Fire Fighting Robot Coding


//NOTE that the sensors read higher numbers when the object, or wall, are closer. (The farther, the lower number it is,) 
int ldist; // LEFT SENSOR READ
int fdist; // FRONT SENSOR READ
int rdist; // RIGHT SENSOR READ
int fsense; // FLAME SENSOR READ

// PIN Assignments
int motor1Pin1 = 5; // left forwards (brown wire)    = AIA
int motor1Pin2 = 4; // left backwards (white wire)   = AIB
int motor2Pin1 = 3; // right forwards (red wire)     = BIA
int motor2Pin2 = 2; // right backwards (black wire)  = BIB
int groundPin = 8; // connect ground sensor to pin 8
int fanPin = 10; // connect fan to pin 10

  boolean lClose = false;
  boolean fClose = false;
  boolean rClose = false;
  boolean ltooClose = false;
  boolean ftooClose = false;
  boolean rtooClose = false;
  boolean flameSensed = false;

void setup(){ 
  pinMode(ldist, INPUT);
  pinMode(fdist, INPUT);
  pinMode(rdist, INPUT);
  pinMode(motor1Pin2, OUTPUT);    //motors are in output mode, connected to PWM
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  //pinMode(fanPin, OUTPUT);
  //pinMode(groundPin, INPUT);
  delay(5000);                     //wait 5 seconds before starting. (prevents bot from moving before it is on the floor)
  Serial.begin(19200);            //19200 bits-per-second
  Serial.println("FIRE FIGHTING ROBOT ACTIVATED");
}

/***********************************************************************/
void loop() {
  readSensors();                                  //Read fire sensor and IR sensors
  sensedFire();                                   //if fire is detected, senseFire becomes true
  if (flameSensed = true){                                //senseFire is true, then the fan is on and the motors are off
    blow("on");
    delay(2000);
  } 
  else if (flameSensed = false){
    blow("off");
    followRightWall();               
  }
  flameSensed = false;   
}
/***********************************************************************/

void readSensors()
{
  ldist = analogRead(0);
  fdist = analogRead(1);
  rdist = analogRead(2);
  //fsense = analogRead(4);
            
  Serial.println();
  Serial.println("New Readings and Actions");
  Serial.print("Left"); Serial.print("       ");
  Serial.print("Front"); Serial.print("       ");  
  Serial.print("Right"); Serial.print("       ");
  //Serial.print("Flame Sensor Reads"); Serial.print("       ");
  Serial.println();
  Serial.print(ldist); Serial.print("       ");
  Serial.print(fdist); Serial.print("       ");
  Serial.print(rdist); Serial.print("       ");
  //Serial.print(fsense); Serial.print("       ");
  Serial.println();
  if (ldist > 250)
  {
    lClose = true; 
    Serial.print("LEFT is Close");
  }
  else if (ldist > 500)
  {
    ltooClose = true; 
    Serial.println("LEFT is Too Close");
  }
  if (fdist > 250)
  {
    fClose = true;
    Serial.print("FRONT is Close");
  }
  else if (rdist > 500)
  {
    ftooClose = true;
    Serial.print("FRONT is Too Close");
  }
  if (rdist > 250)
  {
    rClose = true; 
    Serial.print("RIGHT is Close");
  }
  else if (rdist > 500)
  {
    rtooClose = true;
    Serial.print("RIGHT is Too Close");
  }
}

boolean sensedFire()
{
  if (fsense > 300)
  return true;
  else
  return false;
}

void blow(String onoff)
{
  if (onoff = "on")
  digitalWrite(fanPin, HIGH);
  else
  digitalWrite(fanPin, LOW);
}

void followRightWall()
{
  Serial.println("*****************runMotors*****************");
  //DEFAULT: GO FORWARD
  if ( rClose && !rtooClose && !fClose ) // if right is close and front is far, go forward
  {
    Serial.println(" ");
    Serial.print("GO FORWARD");
    Serial.println(" ");
    goForward();  
  }

  if ( lClose && !ltooClose && !fClose ) // if left is close and front is far, go forward
  {
    Serial.println(" ");
    Serial.print("GO FORWARD");
    Serial.println(" ");
    goForward();  
  }

  //STOP
  else if ( fClose && lClose && rClose ) // but if front left right are too ALL close, stop
  {
    Serial.println(" ");
    Serial.print("STOP");
    Serial.println(" ");
    Stop();
  }
      
  //TURN RIGHT
  else if (!rClose) // if the right dist is far, then turn right 
  {
    Serial.println(" ");
    Serial.println("TURN RIGHT");
    Serial.println(" ");
    turnRight();
  }

  else if ( !lClose && rClose && fClose )
  {
    Serial.println(" ");
    Serial.println("TURN LEFT");
    Serial.println("");
    turnLeft();
    //goForward();
  }
}

//********************************************
//Defining Robot's Potential Actions as functions
//Stop, move forward, turn left, turn right
//Call different order of functions depending on the potential
//situations in the maze (3-way fork, left only, etc.)
//********************************************

void Stop()
  {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, LOW);  
  }

void goForward()
  {
  analogWrite(motor1Pin1, 150);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, 150);
  analogWrite(motor2Pin2, LOW);  
  }

void turnRight()
  {
  analogWrite(motor1Pin1, 130);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, 100); 
  }

void turnLeft()
  {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, 100);
  analogWrite(motor2Pin1, 130);
  analogWrite(motor2Pin2, LOW);  
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
