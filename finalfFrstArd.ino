// Fire Fighting Robot Coding

// Include the required Wire library for I2C
#include <Wire.h>

int x = 0;

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
int fanPin = 43; // connect fan to pin 10

  boolean lClose = false;
  boolean fClose = false;
  boolean rClose = false;
  boolean flameSensed = false;


void setup(){ 
  pinMode(motor1Pin2, OUTPUT);    //motors are in output mode, connected to PWM
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(fanPin, OUTPUT);
  Wire.begin(); 
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
    analogWrite(motor1Pin1, LOW);
    analogWrite(motor1Pin2, LOW);
    analogWrite(motor2Pin1, LOW);
    analogWrite(motor2Pin2, LOW); 
    delay(2000);
  } 
  else if (flameSensed == false){
    followRightWall();  
    delay(100);           
  }
  flameSensed = false;   
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
  ldist = analogRead(4);
  fdist = analogRead(5);
  rdist = analogRead(6);
  fsense = analogRead(7);
            
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
  if (ldist > 200)
  {
    lClose = true;  
    Serial.print("LEFT is Close ");
    Serial.println(lClose);
  }
  
  if (fdist > 300)
  {
    fClose = true;
    Serial.print("FRONT is Close ");
    Serial.println(fClose);
  }

  if (rdist > 200)
  {
    rClose = true; 
    Serial.print("RIGHT is Close ");
    Serial.println(rClose);
  }
}


void blow(){
  /*
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(x);              // sends x 
  Wire.endTransmission();    // stop transmitting
  delay(500);
*/
}



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
  }

  else if ( lClose == 0 && rClose == 1 && fClose == 1 )
  {
    Serial.println(" ");
    Serial.println("TURN LEFT");
    Serial.println("");
    turnLeft();
  }

  else
  {
    Stop();
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
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, 255);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, 255);  
  }

void turnRight()
  {
  analogWrite(motor1Pin1, 200);
  analogWrite(motor1Pin2, LOW);
  analogWrite(motor2Pin1, LOW);
  analogWrite(motor2Pin2, 200); 
  }

void turnLeft()
  {
  analogWrite(motor1Pin1, LOW);
  analogWrite(motor1Pin2, 200);
  analogWrite(motor2Pin1, 200);
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
