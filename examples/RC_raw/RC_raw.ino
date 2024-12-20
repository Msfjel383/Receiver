/*
 * RcRaw
 *
 * Get raw rc remote values
 * 
 * This example code is in the public domain.
 */

#include <RC_Receiver.h>

//Create an instance of a receiver
RC_Receiver receiver;

void setup() {
  //Starting Serial
  Serial.begin(9600);
  //initialize the receiver with the pins for each channel
  receiver.init({7, 8, 4, 5});

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
  delay(100);
}
