/*
  Morse.cpp - Library for reading PWM value form an rc reciver
  Created by Nils Lahaye, 2021.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Receiver.h"

#define minMaxLength 2

Receiver::Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6, uint8_t ch7, uint8_t ch8) { init(ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8); } //Set the inputs pins for 8 ch
Receiver::Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6, uint8_t ch7) { init(ch1, ch2, ch3, ch4, ch5, ch6, ch7, 0); } //Set the inputs pins for 7 ch
Receiver::Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6) { init(ch1, ch2, ch3, ch4, ch5, ch6, 0, 0); } //Set the inputs pins for 6 ch
Receiver::Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5) { init(ch1, ch2, ch3, ch4, ch5, 0, 0, 0); } //Set the inputs pins for 5 ch
Receiver::Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4) { init(ch1, ch2, ch3, ch4, 0, 0, 0, 0); } //Set the inputs pins for 4 ch
Receiver::Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3) { init(ch1, ch2, ch3, 0, 0, 0, 0, 0); } //Set the inputs pins for 3 ch
Receiver::Receiver(uint8_t ch1, uint8_t ch2) { init(ch1, ch2, 0, 0, 0, 0, 0, 0); } //Set the inputs pins for 2 ch
Receiver::Receiver(uint8_t ch1) { init(ch1, 0, 0, 0, 0, 0, 0, 0); } //Set the inputs pins for 1 ch

void Receiver::init(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6, uint8_t ch7, uint8_t ch8)//For initalization
{
	//Set local ch pins from the provided pins
	_ch_pin[0] = ch1;
	_ch_pin[1] = ch2;
	_ch_pin[2] = ch3;
	_ch_pin[3] = ch4;
	_ch_pin[4] = ch5;
	_ch_pin[5] = ch6;
	_ch_pin[6] = ch7;
	_ch_pin[7] = ch8;

	//setting all pins as inputs
	pinMode(ch1, INPUT);
	pinMode(ch2, INPUT);
	pinMode(ch3, INPUT);
	pinMode(ch4, INPUT);
	pinMode(ch5, INPUT);
	pinMode(ch6, INPUT);
	pinMode(ch7, INPUT);
	pinMode(ch8, INPUT);
}

void Receiver::setMinMax(int minMax[][minMaxLength]) //set new min and max values
{
	for (int i = 0; i < 8; i++)
	{
		_minMax[i][0] = minMax[i][0];
		_minMax[i][1] = minMax[i][1];
	}
}

long Receiver::getRaw(int ch) {
	return pulseIn(_ch_pin[ch - 1], HIGH); //Return the raw value
}

long Receiver::getMap(int ch) {
	int curI = ch - 1; //set the current index from the channel
	return map(pulseIn(_ch_pin[curI], HIGH), _minMax[curI][0], _minMax[curI][1], 0, 100); //Return the mapped value
}

