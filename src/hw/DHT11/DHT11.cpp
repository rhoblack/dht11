#include "DHT11.h"
#include <wiringPi.h>
#include <iostream>

DHT11::DHT11(int pin)
    : pinNumber(pin)
{
    clearData();
    wiringPiSetup();
}

DHT11::~DHT11()
{

}

void DHT11::clearData()
{
    for (int i=0; i<5; i++) {
        data[i] = 0;
    }
}


void DHT11::startTrigger()
{
    // Start Trigger
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
    delay(18);
    digitalWrite(pinNumber, HIGH);
    pinMode(pinNumber, INPUT);
}

void DHT11::waitResponse()
{
    // read response
    int count = 0;
    while (digitalRead(pinNumber))
    {
        delayMicroseconds(1);
        count++;
        if (count == 255)
            break;
    }
    count = 0;
    while (!digitalRead(pinNumber))
    {
        delayMicroseconds(1);
        count++;
        if (count == 255)
            break;
    }
    count = 0;
    while (digitalRead(pinNumber))
    {
        delayMicroseconds(1);
        count++;
        if (count == 255)
            break;
    }
}

DHT_Data DHT11::readData()
{
    int count = 0;
    clearData();

    startTrigger();
    waitResponse();

    // read data
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            count = 0;
            while (!digitalRead(pinNumber)) // low
            {
                delayMicroseconds(1);
                count++;
                if (count == 255)
                    break;
            }

            count = 0;
            while (digitalRead(pinNumber)) // high
            {
                delayMicroseconds(1);
                count++;
                if (count == 255)
                    break;
            }
            if (count < 50)
                data[i] &= ~(1 << (7 - j));
            else
                data[i] |= (1 << (7 - j));
        }
        //std::cout << "data[" << i << "] : " << data[i] << std::endl;
    }

    dhtData.RH = data[0];
    dhtData.RHDec = data[1];
    dhtData.Temp = data[2];
    dhtData.TempDec = data[3];
    dhtData.checksum = data[4];
    dhtData.error = (data[4] == (data[0] + data[1] + data[2] + data[3])) ? 0 : 1;
    
    //std::cout << "data[4] : " << data[4] << " parity " << ((data[0] + data[1] + data[2] + data[3])) << std::endl;

    return dhtData;
}
