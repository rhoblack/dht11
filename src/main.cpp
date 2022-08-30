#include <iostream>
#include <wiringPi.h>
#include "DHT11.h"

int main()
{
    std::cout << "helloworld" << std::endl;
    DHT11 dht(7);
    DHT_Data dhtData;

    while(1)
    {
        dhtData = dht.readData();
        if (!dhtData.error) {
            std::printf("RH: %d.%d, Temp: %d.%d\n", 
                        dhtData.RH, dhtData.RHDec,
                        dhtData.Temp, dhtData.TempDec);
        }
        delay(3000);
    }

    return 0;
}