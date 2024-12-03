/*
 * RcRaw
 *
 * Get raw rc remote values
 * 
 * This example code is in the public domain.
 */

#include <RC_Receiver.h>

//Create an instance of a receiver
//You can put up to 8 channels pin with one receiver instance
//ex : RC_Receiver receiver('ch1','ch2','ch3','ch4','ch5','ch6','ch7','ch8');
std::vector<uint8_t> pins = {7, 8, 4, 5}; // Beispiel-Pins
RC_Receiver receiver(pins);


void setup() {
  //Starting Serial
  Serial.begin(9600);
  receiver.init(pins); //init the receiver
  Serial.println("Ready");
}

void loop() {
   //prints receiver raw val
   Serial.print(receiver.getRaw(1));
   Serial.print("\t");  
   Serial.print(receiver.getRaw(2));
   Serial.print("\t");  
   Serial.print(receiver.getRaw(3));
   Serial.print("\t");  
   Serial.print(receiver.getRaw(4));
   Serial.print("\t");  
   Serial.println();
}
