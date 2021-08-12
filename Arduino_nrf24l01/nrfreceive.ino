#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeIn =  0xE8E8F0F0E1LL;
float R1 = 8200;
float logR2, R2, T, Tc;

RF24 radio(9, 10);

// The sizeof this struct should not exceed 32 bytes
struct PacketData {
  float tps;
  int rpm;
  float bpsr;//a1
  float cts;
  float eop;//a7
  float cts2;
};

PacketData data;

void setup()
{
  Serial.begin(115200); // Set up radio module
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(false);
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}

unsigned long packetsRead = 0;
void recvData()
{  
  while ( radio.available() ) {        
    radio.read(&data, sizeof(PacketData));
    float tpsval = data.tps;
    int rpmval = data.rpm;
    float bpsrval = data.bpsr;
    float ctsval = data.cts;
    float eopval = data.eop;
    float ctsval2=data.cts2;
    R2=(ctsval2*R1)/(5-ctsval2);
    logR2 = log(R2);
    T = (1/(((logR2-5.7745515455)/3478.72)+0.0028316579));
    Tc = T - 273.15;
    
    char text[40];
    Serial.print(tpsval);
    Serial.print(",");
    Serial.print(rpmval);
    Serial.print(",");
    Serial.print(bpsrval);
    Serial.print(",");
    Serial.print(ctsval);
    Serial.print(",");
    Serial.print(eopval);
    Serial.print(",");
    Serial.print(Tc);
    Serial.print("\n");
    //sprintf(text, "%f,%d,%f,%f,%f\n",data.tps, data.rpm, data.bpsr,data.cts,data.eop);
    //Serial.println(text);
    packetsRead++;
  }
}


void loop()
{
  recvData();
}
