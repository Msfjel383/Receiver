/*
 * RC Mapped
 *
 * Get rc remote value mapped from 0 to 1000
 * 
 * This example code is in the public domain.
 */

#include <RC_Receiver.h>

//Create an instance of a receiver
RC_Receiver receiver;

//Channel min and max value
//Use the RC_raw script to get the min max val by moving your joystick up and down
//This need to be combined with the receiver.setMinMax(minMax); call
//Leave the default value for the un used channels
//First val is the min and the second is the max
//Invert the min and max val to reverse
std::vector<std::pair<uint16_t, uint16_t>> minMax = 
{
  {544,2400}, 
	{544,2400}, 
	{544,2400}, 
	{544,2400} 
};
//define the pins for each channel in this vector
std::vector<uint8_t> pins = {7, 8, 4, 5};

void setup() {
  //Starting Serial
  Serial.begin(9600);
  //initialize the receiver with the pins for each channel and the min max values
  receiver.init(pins, minMax); 

  Serial.println("Ready");
}

void loop() {
   //prints receiver mapped val
   Serial.print(receiver.getMap(1));
   Serial.print("\t");  
   Serial.print(receiver.getMap(2));
   Serial.print("\t");  
   Serial.print(receiver.getMap(3));
   Serial.print("\t");  
   Serial.print(receiver.getMap(4));
   Serial.print("\t");  
   Serial.println();
  delay(100);
}