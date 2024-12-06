# Modified to be non blocking to keep loop fast.
This Library has been forked and modified to use interrupt pin for mesuring the signals frome an RC receiver. Resulting in fast nonblocking main loop execution.

#works only on ESP32 Bords!


# ESP32 Receiver Library

 ESP32 Library for reading rc reciver values using interrupts

## Installing the Library
### Form repo
Clique the code button
Then download as zip
Then in the arduino IDE install the zip library
See [arduino official guide](https://www.arduino.cc/en/guide/libraries)

## How to use
### Import the library 
```c++
#include <RC_Receiver.h>
```

### Initalise the receiver
you can use fewer channels but the max is 8 per instance
```c++
RC_Receiver receiver('ch1 pin','ch2 pin','ch3 pin','ch4 pin','ch5 pin','ch6 pin','ch7 pin','ch8 pin');
````

### Set custom Min and Max value for the mapping
Set custom values for the range of the controller.
The value can be found by using the RC_raw example and moving the joystick to there min and max positon and reading the value
Inverting the min and max will reverse the values 
```c++
int minMax[8][2] = 
{
	{2020,1010}, 
	{1010,2020}, 
	{1010,2020}, 
	{1010,2020}, 
	{1010,2020}, 
	{1010,2020}, 
	{1010,2020}, 
	{1010,2020}
};

void setup() {
	receiver.setMinMax(minMax);
}

```

### Get raw values
getRaw(int ch) will return the raw value form the controller
The `ch` is the channel number
```c++
Serial.print(receiver.getRaw(int ch));
```

### Get mapped values
getMap(int ch) will return the mapped value (0 to 1000) form the controller
The `ch` is the channel number
```c++
Serial.print(receiver.getMap(int ch));
```
