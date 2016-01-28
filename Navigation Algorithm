// Fire Fighting Robot Coding

int ldist; // LEFT SENSOR READ
int fdist; // FRONT SENSOR READ
int rdist; // RIGHT SENSOR READ

// PIN Assignments
int switchPin = 12; // Pin for switch 
int motor1Pin1 = 4; // left backwards (white wire)
int motor1Pin2 = 5; // left forwards (brown wire)
int motor2Pin2 = 6; // right backwards (red wire) 
int motor2Pin1 = 7; // right forwards (black wire)
/*
int groundPin = 8; // connect ground sensor to pin 8
int flamePin = 9; // connect flame sensor ro pin 9
int fanPin = 10; // connect fan to pin 10
*/

int led = 11;

boolean currentState = LOW;  

void setup(){ 
  pinMode(switchPin, INPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  
  /*
  pinMode(groundPin, OUTPUT);
  pinMode(flamePin, OUTPUT);
  pinMode(fanPin, OUTPUT);
  */
  
  pinMode(led, OUTPUT);
    Serial.begin(9600);
  while(digitalRead(switchPin) != HIGH) {
    digitalWrite(led, LOW);
  }
}
  
void loop() {
  currentState = digitalRead(switchPin);
  //currentState = HIGH;
      if (currentState == HIGH) { //if switch is flicked on
      digitalWrite(led, HIGH); // light turns on
      
     ldist = analogRead(A1);
     fdist = analogRead(A2);
     rdist = analogRead(A3);
     
      Serial.println("Left Sensor Reads: "); 
      Serial.println(ldist);
      Serial.println("Front Sensor Reads: ");
      Serial.println(fdist);
      Serial.println("Right Sensor Reads: ");
      Serial.println(rdist);
              
              if (ldist < 400 && fdist < 500) { // when add left sensor include && dist3 < 400 
                // go forwards
               Serial.println("Moving Forward");
               Serial.println();
                digitalWrite(motor1Pin1, LOW);
                digitalWrite(motor1Pin2, HIGH);
                digitalWrite(motor2Pin1, HIGH);
                digitalWrite(motor2Pin2, LOW);  
                delay(300);
                
              } 
              
              if (fdist >= 400){
                  // STOP
                Serial.println("Obstruction Ahead");
                Serial.println();
                digitalWrite(motor1Pin1, LOW);
                digitalWrite(motor1Pin2, LOW);
                digitalWrite(motor2Pin1, LOW);
                digitalWrite(motor2Pin2, LOW); 
               delay(300);
              
                 //GO BACKWARDS
               Serial.println("Moving Back");
               Serial.println();
                digitalWrite(motor1Pin1, HIGH);
                digitalWrite(motor1Pin2, LOW);
                digitalWrite(motor2Pin1, LOW);
                digitalWrite(motor2Pin2, HIGH);  
               delay(300); 
               }
              
              
              if (rdist > 500) {
              //Right Sensor detects something less 23cm away
              // Result need to TURN Left
              Serial.println("Left Turn");
              Serial.println();
                digitalWrite(motor1Pin1, HIGH);
                digitalWrite(motor1Pin2, LOW);
                digitalWrite(motor2Pin1, HIGH);
                digitalWrite(motor2Pin2, LOW);  
                delay (300);
              }
            
            if (ldist > 400) {
              //Left Sensor detects something less 23cm away
              // Result need to TURN Right
                digitalWrite(motor1Pin1, HIGH);
                digitalWrite(motor1Pin2, LOW);
                digitalWrite(motor2Pin1, LOW);
                digitalWrite(motor2Pin2, HIGH);  
            }
    
    else if(currentState == LOW){ 
      Serial.println("OFF");
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        digitalWrite(led, LOW); // ADDED NOW  
      }
      delay(1000); // if not 1000 will get jittery
    
      }
}
