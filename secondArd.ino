// Include the required Wire library for I2C<br>
#include <Wire.h>
int fanPin = 8;
int x = 0;
int a = 0; 
void setup() {
  // Define the fanPin pin as Output
  pinMode (fanPin, OUTPUT);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}
void receiveEvent(int bytes) {
  a = Wire.available();
  x = Wire.read();    // read one character from the I2C
  Serial.print("a = ");
  Serial.println(a);
  Serial.print("x = ");
  Serial.println(x);
}
void loop() {
  //If value received is 0 blink fanPin for 200 ms
  if (x == 1) {
    digitalWrite(fanPin, HIGH);
    Serial.println("x = 1, fanPin is on");
    delay(100);
    digitalWrite(fanPin, LOW);
    delay(100);
  }
  //If value received is 3 blink fanPin for 400 ms
  else {
    //digitalWrite(fanPin, HIGH);
    Serial.println("x = 0, fanPin is off");
    //delay(1000);
    digitalWrite(fanPin, LOW);
    delay(1000);
  }
}
