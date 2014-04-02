/*
 Fade
 
 This example shows how to fade an LED on pin 9
 using the analogWrite() function.
 
 This example code is in the public domain.
 */

int red1 = 11;           // the pin that the LED is attached to
int green1 = 10;
int yellow1 = 9;
int red2 = 6;
int green2 = 5;
int yellow2 = 3;

int brightness = 0;    // how bright the LED is
int fadeAmount = 15;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup()  { 
  // declare pin 9 to be an output:
  pinMode(red1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(yellow1, OUTPUT);  
  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(yellow2, OUTPUT);
} 

// the loop routine runs over and over again forever:
void loop()  { 
  // set the brightness of pin 9:
  analogWrite(red1, brightness);
  delay(30); 
  analogWrite(green1, brightness);
  delay(30); 
  analogWrite(yellow1, brightness);
  delay(30); 
  analogWrite(red2, brightness);
  delay(30); 
  analogWrite(green2, brightness);
  delay(30); 
  analogWrite(yellow2, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}
