/*
HOW TO WIRE THE IR SENSOR TO ARDUINO
-Connect the Red wire to power (3.3v)
-Connect the Black wire to ground (GND)
-Connect the 3rd wire to an analog port
*/
int x;

void setup()
{
 Serial.begin(9600); 
}

void loop()
{
 x = analogRead(1); //set x = data from analog port A#
 Serial.println(x); //Print the result 'x'
 if (x > 400){
     Serial.println(" --> Object is close!");
 }
 delay(1000); //Delay the output by 1s (1000ms) 
}
