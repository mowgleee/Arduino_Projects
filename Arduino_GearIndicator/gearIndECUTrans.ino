#include <SPI.h>
#include <mcp_can.h>
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


MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(115200);
    while (CAN_OK != CAN.begin(CAN_250KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Module Failed to Initialized");
        Serial.println("Retrying....");
        delay(200);
    }    
    Serial.println("CAN BUS Module Initialized!");  
}


void loop()
{
    
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
       CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

       rxId= CAN.getCanId();
       if (rxId==0xCFFF048)
       {
       HighByte=buf[1];
       LowByte=buf[0];
       rpm=HighByte*256+LowByte;    
       }
      if (rxId==0xCFFF448)
       {
       HighByte=buf[3];
       LowByte=buf[2];
       rpmt=HighByte*256+LowByte;
       rpmt=rpmt*0.2;
       rpmt=rpmt*60/24;
       }
      rpmratio=rpm/rpmt;
  if (pow(cons_gear1-rpmratio,2)<pow(0.1,2))//0.38
  {
    Serial.println("Gear 1");
  }
  else if (pow(cons_gear2-rpmratio,2)<pow(0.1,2))//0.3
  { 
    Serial.println("Gear 2");
  }
  else if (pow(cons_gear3-rpmratio,2)<pow(0.1,2))//0.3
  {
    Serial.println("Gear 3");
  }
  else if (pow(cons_gear4-rpmratio,2)<0.03)//0.18
  {
    Serial.println("Gear 4");
  }
  else if (pow(cons_gear5-rpmratio,2)<0.05)//0.27
  {
    Serial.println("Gear 5");
  }
  else if (pow(cons_gear6-rpmratio,2)<0.1)//0.27
  {
    Serial.println("Gear 6");
  }
  delay(10);
    }
    Serial.println(rpmt);
    
}
