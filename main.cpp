// main.cpp : Defines the entry point for the console application.  
//  

#include "SerialPort.h"  
#include <iostream>  

int main()
{
    CSerialPort mySerialPort;
    mySerialPort.InitPort(3, CBR_9600, 'E', 8, 1, EV_RXCHAR);
    mySerialPort.OpenListenThread();
    while(true)
    {
        if (mySerialPort.GetBytesInCOM() != 0)
        {
            char rxBuffer;
            mySerialPort.ReadChar(rxBuffer);
            std::cout << rxBuffer;
        }
    }
    return 0;
}