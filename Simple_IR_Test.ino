int x;

void setup()
{
 Serial.begin(9600); 
}

void loop()
{
 x = analogRead(1); //set x = data from analog port A#
 Serial.println(x); //Print the result 'x'
 delay(1000); //Delay the output by 1s (1000ms) 
}
