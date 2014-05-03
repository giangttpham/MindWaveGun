// named constants for the switch and motor pins
const int motorPin =  9; // the number of the motor pin
const int relayPin = 2;	    // use this pin to drive the transistor


void setup() {
  // initialize the motor pin as an output:
  pinMode(motorPin, OUTPUT);  
  pinMode(relayPin, OUTPUT);  
  // initialize the switch pin as an input:
}

void loop(){
  // read the state of the switch value:
  digitalWrite(relayPin,HIGH);
  delay(500);
  digitalWrite(motorPin, HIGH);  
  delay(1000);
    digitalWrite(motorPin, LOW); \
    digitalWrite(relayPin,LOW);
      delay(1000);

  
}
