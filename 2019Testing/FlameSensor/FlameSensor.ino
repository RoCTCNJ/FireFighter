//Define constants
const int sensorMin = 0;
const int sensorMax = 1024;

//Initialize variables/pins
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

//Main code
void loop() {
  //Read flame sensor from port A0
  int sensorReading = analogRead(A0);
  //Map reading to 1 of 3 values
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  //Print results
  switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close Fire **");
    break;
  case 1:    // A fire between 1-3 feet away.
    Serial.println("** Distant Fire **");
    break;
  case 2:    // No fire detected.
    Serial.println("No Fire");
    break;
  }
  //Wait 1000 ms (1s) before repeating loop
  delay(1000);
}
