
//int switchPin = 12; // Pin for switch 
int motor1Pin1 = 2; // left backwards (white wire)
int motor1Pin2 = 3; // left forwards (brown wire)
int motor2Pin2 = 4; // right backwards (red wire) 
int motor2Pin1 = 5; // right forwards (black wire)


void setup() {
  //pinMode(switchPin, INPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);

  Serial.begin(9600);
  //digitalWrite(motor1Pin1, HIGH);
  //digitalWrite(motor1Pin2, HIGH);
  //digitalWrite(motor2Pin1, HIGH);
  //digitalWrite(motor2Pin2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(motor1Pin1, HIGH);    //motor 1 will go forward then delay for 1 second
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, LOW); 
  digitalWrite(motor2Pin2, LOW); 
  delay(2000);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);    //motor 1 will go backward then delay for 1 second
  digitalWrite(motor2Pin1, LOW); 
  digitalWrite(motor2Pin2, LOW); 
  delay(2000);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH);    //motor 2 will go forward then delay for 1 second
  digitalWrite(motor2Pin2, LOW); 
  delay(2000);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, LOW); 
  digitalWrite(motor2Pin2, HIGH);    //motor 2 will go backward then delay for 1 second
  delay(2000);
}
