#include <SPI.h>
#include "mcp_can.h"


long unsigned int rxId;

unsigned long rcvTime;

unsigned char len = 0;
unsigned char buf[8];
int HighByte=0;
int LowByte=0;
int rpm=0;


const int SPI_CS_PIN = 10;


MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(9600);
    

    while (CAN_OK != CAN.begin(CAN_250KBPS))              // init can bus : baudrate = 250k
    {
        Serial.println("CAN BUS Module Failed to Initialized");
        Serial.println("Retrying....");
        delay(200);
    }    
    Serial.println("CAN BUS Module Initialized!");
    //Serial.println("Time\t\tPGN\t\tByte0\tByte1\tByte2\tByte3\tByte4\tByte5\tByte6\tByte7");    
}


void loop()
{
    
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        rcvTime = millis();
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
        rxId= CAN.getCanId();
        Serial.println(rxId);
        Serial.println(len);
        delay(25);
        
    
    }
}
