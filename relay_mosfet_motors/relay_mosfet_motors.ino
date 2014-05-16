// named constants for the switch and motor pins
const int motorPin =  9; // the number of the motor pin
const int relayPin = 2;	    // use this pin to drive the transistor


void setup() {
  // initialize the motor pin as an output:
  pinMode(motorPin, OUTPUT);  
  pinMode(relayPin, OUTPUT);  
  // initialize the switch pin as an input:
}

void loop() {
    digitalWrite(motorPin, HIGH);  

 // digitalWrite(relayPin,HIGH);
  //delay(500);
  delay(5000);
  digitalWrite(motorPin, LOW);
  //digitalWrite(relayPin,LOW);
  delay(10000);
}

