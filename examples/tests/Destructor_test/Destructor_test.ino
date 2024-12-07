/*
 * Destructor test
 *
 * Test the destructor of the RC_Receiver class to ensure that the interrupt is disabled annd ready for the next instance
 * 
 * This example code is in the public domain.
 */

#include <RC_Receiver.h>

//Create an instance of a receiver


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
   

  Serial.println("Ready");
}
void test(){
  RC_Receiver receiver;
receiver.init(pins, minMax);
  while(millis()<10000){
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
}
void test2(){
  RC_Receiver receiver;
  receiver.init(pins, minMax);
  while(millis()<30000){
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
}


void loop() {
  //first instance
  test();
  //destroy the first instance
  //wait 10 sec
  while(millis()<20000){
    Serial.println("Loop");
    delay(1000);
  }
  //second instance
  test2();
  //destroy the second instance
  //wait infinite
  while(true){
    Serial.println("Loop2");
    delay(1000);
  }
}


