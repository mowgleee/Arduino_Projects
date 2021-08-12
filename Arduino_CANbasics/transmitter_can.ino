// Henry's Bench
// 1st CAN Network - CAN TRANSMIT
#include <SPI.h>
#include <mcp_can.h>



const int SPI_CS_PIN = 10;

// Build an ID or PGN

long unsigned int txID = 0xCFFF047; // This format is typical of a 29 bit identifier.. the most significant digit is never greater than one.
unsigned char stmp[8] = {5,0,0,0,0,0,0,0};

//Construct a MCP_CAN Object and set Chip Select to 10.

MCP_CAN CAN(SPI_CS_PIN);                            


void setup()
{
    Serial.begin(9600);

    while (CAN_OK != CAN.begin(CAN_250KBPS))              // init can bus : baudrate = 250K
    {
         Serial.println("CAN BUS Module Failed to Initialized");
        Serial.println("Retrying....");
        delay(200);
        
    }
    Serial.println("CAN BUS Shield init ok!");
}


void loop()
{   Serial.println("In loop");

    // send the data:  id = 0x00, Extended Frame, data len = 8, stmp: data buf
    // Extended Frame = 1.
    
    CAN.sendMsgBuf(txID,0, 8, stmp);    
    delay(25);    // send data every 0
}
