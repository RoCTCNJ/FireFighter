//DEFUNCT AS OF 10/28/16
//fan testing
int fanPin = 8;

void setup()
{
  pinMode(fanPin, OUTPUT);    //motors are in output mode, connected to PWM
  Serial.begin(9600); 
}

void loop()
{
   digitalWrite(fanPin, HIGH);
   Serial.println("Fan ON");
   delay(2000);
   digitalWrite(fanPin, LOW);
   Serial.println("Fan OFF");
   delay(2000);  
}
