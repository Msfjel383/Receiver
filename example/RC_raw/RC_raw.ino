/*
 * RcRaw
 *
 * Get raw rc remote values
 * 
 * This example code is in the public domain.
 */

#include <Receiver.h>

//Create an instance of a receiver
//You can put up to 8 channels pin with one receiver instance
//ex : Receiver receiver('2','3','4','5','6','7','8','9',);
Receiver receiver(2,3,4,5);


void setup() {
  //Starting Serial
  Serial.begin(9600);
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
