/*
  RC_Receiver.h - Library for reading PWM value form an rc reciver
  Created by Nils Lahaye, 2022.
  Released into the public domain.
*/
#ifndef RC_Receiver_h
#define RC_Receiver_h

#include "Arduino.h"

#define minMaxLength 2

class RC_Receiver
{
    public:
        RC_Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6, uint8_t ch7, uint8_t ch8); //Set the inputs pins for 8 ch
        RC_Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6, uint8_t ch7); //Set the inputs pins for 7 ch
        RC_Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6); //Set the inputs pins for 6 ch
        RC_Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5); //Set the inputs pins for 5 ch
        RC_Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4); //Set the inputs pins for 4 ch
        RC_Receiver(uint8_t ch1, uint8_t ch2, uint8_t ch3); //Set the inputs pins for 3 ch
        RC_Receiver(uint8_t ch1, uint8_t ch2); //Set the inputs pins for 2 ch
        RC_Receiver(uint8_t ch1); //Set the inputs pins for 1 ch

        void setMinMax(int minMax[][minMaxLength]);//Setting the MinMax val

        void init(uint8_t ch1, uint8_t ch2, uint8_t ch3, uint8_t ch4, uint8_t ch5, uint8_t ch6, uint8_t ch7, uint8_t ch8);//For initalization

        long getRaw(int ch); //Send the raw values

        long getMap(int ch); //Send the mapped values (0 to 100)

    private:
        uint8_t _ch_pin[8]; //Local pins array
        int _minMax[8][minMaxLength] = { {1010,2020}, {1010,2020}, {1010,2020}, {1010,2020}, {1010,2020}, {1010,2020}, {1010,2020}, {1010,2020} }; //Local double array of the min and max for the mapping with the default values
};

#endif