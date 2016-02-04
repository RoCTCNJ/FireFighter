#include <Servo.h>

// create servo objects
Servo leftMotor;
Servo rightMotor;

const int serialPeriod = 250;       // only print to the serial console every 1/4 second
unsigned long timeSerialDelay = 0;

const int loopPeriod = 20;          // a period of 20ms = a frequency of 50Hz
unsigned long timeLoopDelay   = 0;

// specify the trig & echo pins used for the ultrasonic sensors
const int ultrasonic2TrigPin = 8;
const int ultrasonic2EchoPin = 9;

int ultrasonic2Distance;
int ultrasonic2Duration;

// define the states
#define DRIVE_FORWARD     0
#define TURN_LEFT         1

int state = DRIVE_FORWARD; // 0 = drive forward (DEFAULT), 1 = turn left

void setup()
{
    Serial.begin(9600);
  
    // ultrasonic sensor pin configurations
    pinMode(ultrasonic2TrigPin, OUTPUT);
    pinMode(ultrasonic2EchoPin, INPUT);
    
    leftMotor.attach(12);
    rightMotor.attach(13);
}


void loop()
{
    debugOutput(); // prints debugging messages to the serial console
    
      if(millis() - timeLoopDelay >= loopPeriod)
      {
          //ledBlink;
          readUltrasonicSensors(); // read and store the measured distances
          stateMachine();
          timeLoopDelay = millis();
      }
}

/*void ledBlink()
{
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}
*/

void stateMachine()
{
    if(state == DRIVE_FORWARD) // no obstacles detected
    {
        if(ultrasonic2Distance > 8 || ultrasonic2Distance < 0) // if there's nothing in front of us (note: ultrasonicDistance will be negative for some ultrasonics if there's nothing in range)
        {
            // drive forward
            rightMotor.write(180);
            leftMotor.write(0);
        }
        else // there's an object in front of us
        {
            state = TURN_LEFT;
        }
    }
    else if(state == TURN_LEFT) // obstacle detected -- turn left
    {
        unsigned long timeToTurnLeft = 700; // it takes around 1.1 seconds to turn 90 degrees
        
        unsigned long turnStartTime = millis(); // save the time that we started turning

        while((millis()-turnStartTime) < timeToTurnLeft) // stay in this loop until timeToTurnLeft (1.1 seconds) has elapsed
        {
            // turn left
            rightMotor.write(0);
            leftMotor.write(0);
        }
        
        state = DRIVE_FORWARD;
    }
}


void readUltrasonicSensors()
{
    // ultrasonic 2
    digitalWrite(ultrasonic2TrigPin, HIGH);
    delayMicroseconds(10);                  // must keep the trig pin high for at least 10us
    digitalWrite(ultrasonic2TrigPin, LOW);
    
    ultrasonic2Duration = pulseIn(ultrasonic2EchoPin, HIGH);
    ultrasonic2Distance = (ultrasonic2Duration/2)/29;
}


void debugOutput()
{
    if((millis() - timeSerialDelay) > serialPeriod)
    {
        Serial.print("ultrasonic2Distance: ");
        Serial.print(ultrasonic2Distance);
        Serial.print("cm");
        Serial.println();
        
        timeSerialDelay = millis();
    }
}
