////////////////////////////////////////////////////////////////////////
// Arduino Interface with Mindwave
// 
// This is example code provided by NeuroSky, Inc. and is provided
// license free.
////////////////////////////////////////////////////////////////////////

//#define MOTOR 3
#define BAUDRATE 115200
#define DEBUGOUTPUT 0

#define EEG_FREQ_BANDS 8

//8 frequency band
uint32_t eegPower[EEG_FREQ_BANDS];
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = { 0};
byte signal[64] = {0};  
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

// system variables
long lastReceivedPacket = 0;
boolean bigPacket = false;

boolean loaded = 0;
boolean shot = 0;

//motor controls
const int relayPin = 2;	    // use this pin to drive the transistor

// named constants for the switch and motor pins
const int motorPin =  9; // the number of the motor pin

//////////////////////////
// Microprocessor Setup //
//////////////////////////
void setup() {
  pinMode(relayPin, OUTPUT);  // set pin as an output
   // initialize the motor pin as an output:
  //pinMode(motorPin, OUTPUT);      

  //pinMode(MOTOR, OUTPUT);
  Serial.begin(BAUDRATE);           // USB

  delay(3000) ;
  Serial.write(194) ;
    digitalWrite(relayPin, LOW);  // turn the relay on        
   digitalWrite(motorPin, LOW);
 delay(3000) ;
}

////////////////////////////////
// Read data from Serial UART //
////////////////////////////////
byte ReadOneByte() {
  int ByteRead;

  while(!Serial.available());
  ByteRead = Serial.read();

#if DEBUGOUTPUT  
  Serial.print((char)ByteRead);   // echo the same byte out the USB serial (for debug purposes)
#endif

  return ByteRead;
}

/////////////
//MAIN LOOP//
/////////////
void loop() {


  // Look for sync bytes
  if(ReadOneByte() == 170) {
    if(ReadOneByte() == 170) {

      payloadLength = ReadOneByte();
      if(payloadLength > 169)                      //Payload length can not be greater than 169
          return;

      generatedChecksum = 0;        
      for(int i = 0; i < payloadLength; i++) {  
        payloadData[i] = ReadOneByte();         //Read payload into memory
        signal[i] = payloadData[i];
        generatedChecksum += payloadData[i];
      }   

      checksum = ReadOneByte();                      //Read checksum byte from stream      
      generatedChecksum = 255 - generatedChecksum;   //Take one's compliment of generated checksum

        if(checksum == generatedChecksum) {    

        poorQuality = 200;
       // signal = 0;
        attention = 0;
        meditation = 0;

        for(int i = 0; i < payloadLength; i++) {    // Parse the payload
          switch (payloadData[i]) {
          case 2: //Code 0x02: check poor quality
            i++;            
            poorQuality = payloadData[i];
            bigPacket = true;            
            break;
          case 4: //Code 0x04: Attention Esense
            i++;
            attention = payloadData[i];                        
            break;
          case 5: //code 0x05: Mediation Esense
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
            break;
          case 0x83: //code 0x83: 8 commonly regconised EEG brainwaves
            
            for (int j = 0; j< EEG_FREQ_BANDS; j++)
            {
                     eegPower[j] = ((uint32_t)signal[++i] << 16) | ((uint32_t)signal[++i] << 8) | (uint32_t)signal[++i];
            }
            
  
            break;
          default:
            break;
          } // switch
        } // for loop

#if !DEBUGOUTPUT
        if(bigPacket) {
          //print data to the serial monitor
          Serial.print("PoorQuality: ");
          Serial.print(poorQuality, DEC);
          Serial.print(" Attention: ");
          Serial.print(attention, DEC);
          Serial.print(" Time since last packet: ");
          Serial.println(millis() - lastReceivedPacket, DEC);
          lastReceivedPacket = millis();

          Serial.println("Frequency bands:");
          for (int i = 0; i < EEG_FREQ_BANDS; i++) 
          {
            Serial.print(eegPower[i],DEC);
            Serial.print("\t");
          }
          Serial.println();
          
          //pick the brainwave type with the highest signal
          int max_freq_pos = maxFrequency(eegPower);
          Serial.print("Max Frequency is ");
          Serial.print(eegPower[max_freq_pos],DEC);
          Serial.print(" with index ");
          Serial.println(max_freq_pos); 
          
          //EEG sinal order: 0 - Delta, 1 - Theta; 2 - Low Alpha; 3 - High Alpha
          //4 - Low Beta; 5 - High Beta; 6 - Mid Gamma; 7 - High Gamma
          switch(max_freq_pos)
          {
            case 0:
              Serial.println("Strongest brainwave type: Delta");
              break;
            case 1:
              Serial.println("Strongest brainwave type: Theta");
              break;
            case 2:
              Serial.println("Strongest brainwave type: Low alpha");
              break;
            case 3:
              Serial.println("Strongest brainwave type: High alpha");
              break;
            case 4:
              Serial.println("Strongest brainwave type: Low Beta");
              break;
            case 5:
              Serial.println("Strongest brainwave type: High Beta");
              break;
            case 6:
              Serial.println("Strongest brainwave type: Low Gamma");
              break;
            case 7:
              Serial.println("Strongest brainwave type: Mid Gamma");
              break;
          }
        
          //if attention is over 30 and the brainwave is either low/high beta, run the motors
          Serial.println();
          if (attention >= 30 && ( max_freq_pos == 4 || max_freq_pos == 5))
          {
            digitalWrite(relayPin, HIGH);  // turn the relay on        
            digitalWrite(motorPin, HIGH);
            delay(5010);              
          }
            digitalWrite(relayPin, LOW);  // turn the relay on        
            digitalWrite(motorPin, LOW);
            delay(4000);           
        }
#endif        
        bigPacket = false;        
      }
      else {
        // Checksum Error
      }  // end if else for checksum
    } // end if read 0xAA byte
  } // end if read 0xAA byte
}


//Function to select the brainwave type with the highest signal
int maxFrequency(uint32_t eegPower[EEG_FREQ_BANDS])
{
  int max_freq_index = 0;
  uint32_t max_freq = eegPower[max_freq_index];
  
  for (int i = 1; i < EEG_FREQ_BANDS; i++)
  {
    if (max_freq < eegPower[i])
    {
      max_freq_index = i;
      max_freq = eegPower[max_freq_index];
    }
  }
  
  return max_freq_index;
}  


