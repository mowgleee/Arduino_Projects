#include <Adafruit_VL53L0X.h>
#include <SoftwareSerial.h>
SoftwareSerial HC12(10,11); // HC-12 TX Pin, HC-12 RX Pin
unsigned long rtimer=0;
unsigned long ttimer=0;
unsigned long sd=0;
int c=0;
unsigned long atimer=0;
unsigned long btimer=0;
unsigned long diff=0;


Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(2400);
  HC12.begin(2400);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {
   atimer=millis();
   if(HC12.available()>0 && c==0){
     ttimer=millis();
     Serial.println("data available");
     c=1;
     diff=ttimer-atimer;
  }
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if ((measure.RangeStatus != 4)&& (measure.RangeMilliMeter<1000)) {  // phase failures have incorrect data
    
    rtimer=millis();
    sd=rtimer-ttimer;
    Serial.println(diff/1000.000);
    Serial.println((sd+100)/1000.000);
  } else {
  }
    
  delay(10);
}
