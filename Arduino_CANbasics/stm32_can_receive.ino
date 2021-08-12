#include <SPI.h>
//SPI.setMOSI(PB15);
//SPI.setMISO(PB14);
//SPI.setSCLK(PB13);
//SPI.begin();
#include <mcp_can.h>


long unsigned int rxId;

unsigned long rcvTime;

unsigned char len = 0;
unsigned char buf[8];

const int SPI_CS_PIN = PB12;


MCP_CAN CAN;                                    // Set CS pin

void setup()
{   
    SPI.setMOSI(PB15);
    SPI.setMISO(PB14);
    SPI.setSCLK(PB13);
    SPI.begin();
    pinMode(PC13, OUTPUT);
    CAN.init_CS(SPI_CS_PIN);
    //Serial.begin(9600);
    //Serial.println('a');
    
    while (CAN_OK != CAN.begin(CAN_250KBPS))              // init can bus : baudrate = 500k
    {
        //Serial.println("CAN BUS Module Failed to Initialized");
        //Serial.println("Retrying....");
        digitalWrite(PC13, LOW);
        delay(1000);
        digitalWrite(PC13, HIGH);
        delay(1000);
        digitalWrite(PC13, LOW);
        delay(200);
    }    
    //Serial.println("CAN BUS Module Initialized!");
    //Serial.println("Time\t\tPGN\t\tByte0\tByte1\tByte2\tByte3\tByte4\tByte5\tByte6\tByte7");
    digitalWrite(PC13, LOW);
    
}


void loop()
{
    
     if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
       rcvTime = millis();
       CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

       rxId= CAN.getCanId();

       //Serial.print(rcvTime);
       // Serial.print("\t\t");
       // Serial.print(rxId, HEX);
       // Serial.print("\t");       
       //Serial.print("0x");
       //Serial.print(buf[i], HEX);
       
       //int out=buf[0]*(10000/255);
       //Serial.println(buf[0]);
       if (buf[0]==3)
       {
        digitalWrite(PC13, LOW);
        delay(5000);
       }
       else
       {
        digitalWrite(PC13, HIGH);
        delay(1000);
        digitalWrite(PC13, LOW);
        delay(1000);
       }
       
    }
    else
    {
      digitalWrite(PC13, LOW);
      delay(10000);
    }
 delay(25);
}
