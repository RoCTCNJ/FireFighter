int E3 = 8;
int M3 = 9;

int x;

void setup() 
{ 
    Serial.begin(9600); 
    pinMode(M3, OUTPUT);   
} 

void loop() 
{ 
//Fan Off
digitalWrite(M3,LOW);   
analogWrite(E3, 250);
delay(2000); 

//Flame Sensor
 x = analogRead(0); //set x = data from analog port A#
 Serial.println(x); //Print the result 'x'
 if (x < 50){
     Serial.println(" --> Fire is close!");
         digitalWrite(M3,HIGH);   
         analogWrite(E3, 250);
         delay(2000); 
 }
 delay(1000); //Delay the output by 1s (1000ms) 

}
