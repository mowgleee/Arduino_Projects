#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX

unsigned char re_Buf[11], counter = 0;
unsigned char sign = 0;
byte data_Buf[3] = {0};

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.listen();
  delay(10);
  mySerial.write(0XA5);
  mySerial.write(0X45);    // Enable Output
  mySerial.write(0XEA);
}

void loop() {
  unsigned char i = 0, sum = 0;
  uint16_t distance = 0;
  while (mySerial.available()) {
    re_Buf[counter] = (unsigned char)mySerial.read();
    if (counter == 0 && re_Buf[0] != 0x5A) return;
    counter++;
    if (counter == 8)             // Enough Data available?
    {
      counter = 0;               // Get Ready for the next stream
      sign = 1;
    }
  }
  if (sign)
  {
    sign = 0;
    for (i = 0; i < 7; i++)
      sum += re_Buf[i];
    if (sum == re_Buf[i] )       // Check Header
    {
      data_Buf[0] = re_Buf[4];
      data_Buf[1] = re_Buf[5];
      data_Buf[2] = re_Buf[6];
      distance = data_Buf[0] << 8 | data_Buf[1];

      Serial.print("distance: ");
      Serial.print( distance);
      Serial.print(" mm,mode: ");
      Serial.println( data_Buf[2]);
    }
  }
}
