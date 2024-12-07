/*
 * RC Mapped
 *
 * looptime Test
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

unsigned long looptime;
unsigned long result;
int ch1;
int ch2;
int ch3;
int ch4;
void loop() {
  looptime = micros();
   ch1 = receiver.getMap(1);
   ch2 = receiver.getMap(2);
   ch3 = receiver.getMap(3);
   ch4 = receiver.getMap(4);
  result = micros()-looptime;
   delay(1000);
   //prints receiver mapped val

   Serial.print(ch1);
   Serial.print("\t");  
   Serial.print(ch2);
   Serial.print("\t");  
   Serial.print(ch3);
   Serial.print("\t");  
   Serial.print(ch4);
   Serial.print("\t");  
   Serial.println();
   Serial.print("Looptime in us: ");
   Serial.println(result);
}
