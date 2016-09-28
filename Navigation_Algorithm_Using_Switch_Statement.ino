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
//int groundPin = 8; // connect ground sensor to pin 8
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
  pinMode(fanPin, OUTPUT);
  //pinMode(groundPin, INPUT);
  delay(5000);                     //wait 5 seconds before starting. (prevents bot from moving before it is on the floor)
  Serial.begin(19200);            //19200 bits-per-second
  Serial.println("FIRE FIGHTING ROBOT ACTIVATED");
}

/***********************************************************************/
void loop() {
  readSensors();                                  //Read fire sensor and IR sensors
  flameSensed = sensedFire();                                   //if fire is detected, senseFire becomes true
  if (flameSensed = true){                                //senseFire is true, then the fan is on and the motors are off
    blow("on");
    delay(2000);
  } 
  else if (flameSensed = false){
    blow("off");
    followRightWall();               
  } 
}
/***********************************************************************/

void readSensors()
{
  ldist = analogRead(0);
  fdist = analogRead(1);
  rdist = analogRead(2);
  fsense = analogRead(4);
            
  Serial.println();
  Serial.println("New Readings and Actions");
  Serial.print("Left"); Serial.print("       ");
  Serial.print("Front"); Serial.print("       ");  
  Serial.print("Right"); Serial.print("       ");
  Serial.print("Flame Sensor Reads"); Serial.print("       ");
  Serial.println();
  Serial.print(ldist); Serial.print("       ");
  Serial.print(fdist); Serial.print("       ");
  Serial.print(rdist); Serial.print("       ");
  Serial.print(fsense); Serial.print("       ");
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
  {
    Serial.println(" ");
    Serial.print("FIRE DETECTED");
    Serial.println(" ");
    return true;
  }
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
  switch(rClose)
  {
    case true: //what to do when right wall is close
      if(!fClose) //go forward if the front is open
      {
        Serial.println(" ");
        Serial.print("GO FORWARD");
        Serial.println(" ");
        goForward();
      }
      else if(!lClose)  //turn left if there's a wall in front and the left is open
      {
        Serial.println(" ");
        Serial.print("TURN LEFT");
        Serial.println(" ");
        turnLeft();
      }
      else  //stop if there's a wall on all sides and then let the robot 
            //keep turning left until the front is open
      {
        Serial.println(" ");
        Serial.print("STOP");
        Serial.println(" ");
        Stop();
        Serial.println(" ");
        Serial.print("TURN LEFT");
        Serial.println(" ");
        turnLeft();
      }
      
    case false: //right side is open so turn right
        Serial.println(" ");
        Serial.println("TURN RIGHT");
        Serial.println(" ");
        turnRight();
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
