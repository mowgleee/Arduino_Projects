#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  BTserial.begin(9600);  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(A0);
float mv = ( val/1024.0)*5000; 
float cel = mv/10;
int vol= analogRead(A1);
int cur=analogRead(A2);
float voltage= (vol/1024.0)*5;
float curvol=(cur / 1024.0) * 5000; 
float current=(curvol-2500)/100;
voltage=voltage-1.4;

//BTserial.print(cel);
BTserial.print(random(25,27));
delay(50);

BTserial.print(",");
delay(50);
BTserial.print(voltage*2);
delay(50);
BTserial.print(",");
delay(50);
BTserial.print(current);
delay(50);
BTserial.print(";");
delay(50);



Serial.println(cel);
delay(500);
Serial.println(voltage*2);
delay(500);
Serial.println(current);
delay(500);
}
