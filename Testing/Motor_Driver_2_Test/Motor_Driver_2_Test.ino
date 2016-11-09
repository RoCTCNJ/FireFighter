int E1 = 6; //Speed 1       RIGHT MOTOR
int M1 = 7; //Direction 1   RIGHT MOTOR
int E2 = 5; //Speed 2       LEFT MOTOR         
int M2 = 4; //Direction 2   LEFT MOTOR

//OUTPUT HIGH for Forward
//OUTPUT LOW for Reverse

void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
} 

void loop() 
{ 
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
