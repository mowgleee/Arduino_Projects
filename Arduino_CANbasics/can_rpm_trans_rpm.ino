#include <SPI.h>
#include <mcp_can.h>

long unsigned int rxId;
unsigned long rcvTime;
unsigned char len = 0;
unsigned char buf[8];
const int SPI_CS_PIN = 10;
int HighByte=0;
int LowByte=0;
int rpm=0;
int hall = A0;
float threshold = 24.0;
float start;
int count;
float end_time;
float time_passed;
float rpmt; 
bool state;

MCP_CAN CAN(SPI_CS_PIN);

void setup() {
    Serial.begin(115200);
    pinMode(hall, INPUT);
    while (CAN_OK != CAN.begin(CAN_250KBPS))              // init can bus : baudrate = 250k
    {
        Serial.println("CAN BUS Module Failed to Initialized");
        Serial.println("Retrying....");
        delay(200);
    }    
    Serial.println("CAN BUS Module Initialized!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
//       count = 0;
//  start = millis();
//  state = false;
//  while(true){
//    if (analogRead(hall)>120){
//      if (state==false){
//        state = true;
//        count=count+1;
//      }
//    } else{
//      state = false;
//    }
//    
//    if (count>=threshold){
//      break;
//    }
//  }
//  end_time = millis();
//  time_passed = ((end_time-start)/1000.0);
//  rpmt = (count/(time_passed*24))*60.0;
//  //Serial.println('TRANSMISSION rpm ');
//  Serial.println(rpmt);
//  delay(1);
  
       //rcvTime = millis();
       CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

       rxId= CAN.getCanId();
       Serial.println(rxId);
       if (rxId==0xCFFF048)
       {
       HighByte=buf[1];
       LowByte=buf[0];
       rpm=HighByte*256+LowByte;
        if (rpm>32767)
        {
          rpm=rpm-65536;
        }
        //Serial.println('Engine rpm ');
       Serial.print("\t");
       Serial.print(rpm);    
    }
    }
 delay(10);
}
