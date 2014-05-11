/*
Adafruit Arduino - Lesson 14. Sweep
*/
 
#include <Servo.h> 
 
int servoPin = 4;
 
Servo servo;  
 
int angle = 0;   // servo position in degrees 
 
void setup() 
{ 
  servo.attach(servoPin); 
} 
 
 
void loop() 
{ 
  //return to 0 degree as initial position
  servo.write(0);
 
 
  // scan from 0 to 60 degrees
  for(angle = 0; angle < 60; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 

  // now scan back from 60 to 0 degrees
  for(angle = 90; angle > 60; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  } 
 /
} 
