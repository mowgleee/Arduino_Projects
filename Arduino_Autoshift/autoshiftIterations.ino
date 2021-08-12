#include <SPI.h>
#include <mcp_can.h>
int upbutton=4;
float rpmt; 
long unsigned int rxId;
unsigned char len = 0;
unsigned char buf[8];
const int SPI_CS_PIN = 10;
int rpm=0;
float rpmratio;
double cons_gear1=4.80459;
double cons_gear2=3.4952;
double cons_gear3=2.9126;
double cons_gear4=2.52;
double cons_gear5=2.2788;
double cons_gear6=2.11;
//double err=0.2;
int gearPos=0;
int HighByte=0;
int LowByte=0;
int flag=0;


MCP_CAN CAN(SPI_CS_PIN);      

void setup()
{
    Serial.begin(115200);
    pinMode(upbutton, OUTPUT);
    digitalWrite(upbutton,HIGH);
    while (CAN_OK != CAN.begin(CAN_250KBPS))            
    {
        Serial.println("Retrying....");
        delay(200);
    }    
    Serial.println("Initialized!");  
}

void loop()
{ 
  if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
       CAN.readMsgBuf(&len, buf);
       rxId= CAN.getCanId();
       if (rxId==0xCFFF048)
       {
       HighByte=buf[1];
       LowByte=buf[0];
       rpm=HighByte*256+LowByte;    
       }
  if (rpm>=8500 && flag==0)
    {
      flag=1;
      digitalWrite(upbutton,LOW);
      delay(100);
      digitalWrite(upbutton, HIGH);
      delay(500);
    }   
    if (rpm<8250)
    {
    flag=0;
    }
  delay(10);
 }
}
