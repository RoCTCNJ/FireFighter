//NOTE that the sensors read higher numbers when the object, or wall, are closer. (The farther, the lower number it is,) 
int ldist; // LEFT SENSOR READ
int fdist; // FRONT SENSOR READ
int rdist; // RIGHT SENSOR READ

void setup()
{
 Serial.begin(9600); 
}

void loop()
{
     ldist = analogRead(A4);
     fdist = analogRead(A5);
     rdist = analogRead(A6);
 
  Serial.println("Left Sensor Reads     Front Sensor Reads      Right Sensor Reads "); 
      Serial.print("       ");
      Serial.print(ldist);
      Serial.print("                     ");
      Serial.print(fdist);
      Serial.print("                    ");
      Serial.print(rdist);
      Serial.println();
      
 delay(2000); //Delay the output by 1s (2000ms) 
}

/*
 *  Sample Output
 *  Left Sensor Reads     Front Sensor Reads      Right Sensor Reads 
 *      99                     402                    64
 */
