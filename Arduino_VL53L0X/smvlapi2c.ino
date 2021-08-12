#include "Adafruit_VL53L0X.h"
int lap=0;
unsigned long t2=0;
long t1;
long t;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

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
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if ((measure.RangeStatus != 4)&& (measure.RangeMilliMeter<1000)) {  // phase failures have incorrect data
    t2=millis();
        t=t2-t1;
        t1=t2;
      
      Serial.print("lap");
      Serial.print("\t");
      Serial.print(lap++);
      Serial.print("\n");
      Serial.print("time");
      Serial.print("\t");
      Serial.print((t)/1000.000);
      Serial.print("\n");
      delay(350);
  } else {
  }
    
  delay(10);
}
