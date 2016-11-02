int left, right, front;

int E1 = 6;
int M1 = 7;
int E2 = 5;                         
int M2 = 4; 


void setup()
{
 Serial.begin(9600); 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
}

void loop()
{
//IR Sensors
 left = analogRead(1); //set x = data from analog port A#
 right = analogRead(2);
 front = analogRead(3);
 Serial.print(left); 
 Serial.print(" ");
 Serial.print(front);
 Serial.print(" ");
 Serial.print(right);
 Serial.println();
 delay(1000); //Delay the output by 1s (1000ms) 
 
 
 //Motors
    digitalWrite(M1,HIGH);   
    digitalWrite(M2,HIGH);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control
    delay(2000); 
    
    
    digitalWrite(M1,LOW);   
    digitalWrite(M2,LOW);       
    analogWrite(E1, 250);   //PWM Speed Control
    analogWrite(E2, 250);   //PWM Speed Control
    delay(2000); 
 
}
