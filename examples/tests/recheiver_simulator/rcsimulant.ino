/* RC Receiver Simulator
 * 
 * This code simulates the output of an RC receiver by providing 4 RC Signals by using Servo.h lib.
 * So the library can be tested by connecting two microcontrollers, one with this receiver simulator and the other with the library.
 * 
 * The angles are:
 * CH 1: 90 degrees
 * CH 2: 0 degrees
 * CH 3: 180 degrees
 * CH 4: 45 degrees
 * 
*/

#include <Servo.h>

Servo myservo1;  // create Servo object to simulate the RC signals
Servo myservo2;
Servo myservo3;
Servo myservo4;

void setup() {
  myservo1.attach(9);  // ataach the signals to the pins
  myservo2.attach(10);
  myservo3.attach(11);
  myservo4.attach(13);
}

void loop() {
  
    myservo1.write(90);              // set the angles
    myservo2.write(0);
    myservo3.write(180);
    myservo4.write(45);
    
  
}
