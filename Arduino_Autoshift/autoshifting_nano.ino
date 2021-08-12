#include <SPI.h>
#include <mcp_can.h>
int upbutton=4;
int downbutton=3;
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
    pinMode(downbutton, OUTPUT);
    digitalWrite(upbutton,HIGH);
    digitalWrite(downbutton,HIGH);
    while (CAN_OK != CAN.begin(CAN_250KBPS))            
    {
        Serial.println("Retrying....");
        delay(200);
    }    
    Serial.println("Initialized!");  
}

float readGear(void)
  {
    if(CAN_MSGAVAIL == CAN.checkReceive())           
    {
       CAN.readMsgBuf(&len, buf);   
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
      return rpmratio;
  }
  }

void loop()
{
    rpmratio=readGear();
      while (rpmt==0)
      {
        if (rpm>=8500)
    {
      digitalWrite(downbutton,LOW);
      delay(100);
      digitalWrite(downbutton, HIGH);
      delay(500);
      rpmratio=readGear();
    }   
   }
  while (pow(cons_gear1-rpmratio,2)<pow(0.1,2))//0.38
  {
    Serial.println("Gear 1");
    if (rpm>=9500)
    {
      digitalWrite(upbutton,LOW);
      delay(100);
      digitalWrite(upbutton, HIGH);
      delay(500);
      rpmratio=readGear();
    }
  }
  while (pow(cons_gear2-rpmratio,2)<pow(0.1,2))//0.3
  { 
    Serial.println("Gear 2");
    if (rpm>=9000)
    {
      digitalWrite(upbutton,LOW);
      delay(100);
      digitalWrite(upbutton, HIGH);
      delay(500);
      rpmratio=readGear();
    }
  }
  while (pow(cons_gear3-rpmratio,2)<pow(0.1,2))//0.3
  {
    Serial.println("Gear 3");
    if (rpm>=9000)
    {
      digitalWrite(upbutton,LOW);
      delay(100);
      digitalWrite(upbutton, HIGH);
      delay(500);
      rpmratio=readGear();
    }
  }
  while (pow(cons_gear4-rpmratio,2)<0.03)//0.18
  {
    Serial.println("Gear 4");
    if (rpm>=9000)
    {
      digitalWrite(upbutton,LOW);
      delay(100);
      digitalWrite(upbutton, HIGH);
      delay(500);
      rpmratio=readGear();
    }
  }
  while (pow(cons_gear5-rpmratio,2)<0.05)//0.27
  {
    Serial.println("Gear 5");
    if (rpm>=9000)
    {
      digitalWrite(upbutton,LOW);
      delay(100);
      digitalWrite(upbutton, HIGH);
      delay(500);
      rpmratio=readGear();
    }
  }
  while (pow(cons_gear6-rpmratio,2)<0.1)//0.27
  {
    Serial.println("Gear 6");
    if (rpm>=9000)
    {
      digitalWrite(upbutton,LOW);
      delay(100);
      digitalWrite(upbutton, HIGH);
      delay(500);
      rpmratio=readGear();
    }
  }
  delay(10);
 }
