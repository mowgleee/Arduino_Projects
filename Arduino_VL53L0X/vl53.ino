

//for laser distance sensor CJVL 53L0X v2

#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;
//for laser distance sensor CJVL 53L0X v2

int Clock = A4;
int Data = A5;
int LED = 7;
float distance;

void setup() {
  Serial.begin (9600);
  Wire.begin();
  pinMode (LED, OUTPUT);
  pinMode (Data, INPUT);
  pinMode (Clock, INPUT);
//  pinMode (Servo, OUPPUT);
  sensor.init();
  sensor.setTimeout(500);
}

void loop() {
  distance = (sensor.readRangeSingleMillimeters());
  
  
  Serial.print(sensor.readRangeSingleMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
}
