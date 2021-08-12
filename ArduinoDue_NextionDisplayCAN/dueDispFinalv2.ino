#include <Nextion.h>
#include <due_can.h>

//const int numReadings = 20;     // number of samples for smoothing. The higher, the more smoothing, but slower to react. Default: 20

NexNumber bps = NexNumber(0, 10, "bvalue");
NexNumber tps = NexNumber(0, 11, "tvalue");
NexNumber spee = NexNumber(0, 12, "svalue");
NexNumber cts = NexNumber(0, 13, "tempvalue");
NexNumber rpm = NexNumber(0, 14, "rpm");
NexProgressBar p0= NexProgressBar(0, 2,"tpsbar");
NexProgressBar p2= NexProgressBar(0, 3,"bbar");
NexText gearText=NexText(0,9,"gear");
int upbutton=6;
int downbutton=2;
int butt=27;
int flag=0;

int led1=30;
int led2=33;
int led3=34;
int led4=37;
int led5=38;
int led6=41;
int led7=42;
int led8=45;
int led9=46;
int led10=49;
int led11=50;
int led12=53;

char buffer[100] = {0};
int rpmVal=0;
float tpsVal=0.0;
float ctsVal=0.0;
float bpsVal=0.0;


void setup()
{
  nexInit();
  delay(40);
  pinMode(butt,INPUT_PULLUP);
  pinMode(upbutton, OUTPUT);
  pinMode(downbutton, OUTPUT);
  digitalWrite(upbutton,HIGH);
  digitalWrite(downbutton,HIGH);
  Can0.begin(CAN_BPS_250K);
  int filter;
  for (filter = 0; filter < 3; filter++) 
  {
  Can0.setRXFilter(filter, 0, 0, true);
  }  
  //standard
  for (int filter = 3; filter < 7; filter++) 
  {
  Can0.setRXFilter(filter, 0, 0, false);
  }
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);
  pinMode(led7,OUTPUT);
  pinMode(led8,OUTPUT);
  pinMode(led9,OUTPUT);
  pinMode(led10,OUTPUT);
  pinMode(led11,OUTPUT);
  pinMode(led12,OUTPUT);
}

void loop()
{
  CAN_FRAME incoming;
  if (Can0.available() > 0) {
  Can0.read(incoming);
  if ((incoming.id==218099784))
  printFrame1(incoming);
  if ((incoming.id==218101064))
  printFrame2(incoming);
  if ((incoming.id==218100296))
  printFrame3(incoming);
  }
}

void printFrame1(CAN_FRAME &frame) {
   rpmVal=frame.data.bytes[1]*256+frame.data.bytes[0];
   tpsVal=(frame.data.bytes[3]*256+frame.data.bytes[2])*0.1;
   tps.setValue(tpsVal);
   rpm.setValue(rpmVal);
   p0.setValue((int)tpsVal);
   rpmVal=constrain(rpmVal,0,13000);
   int TachometerRemapedWithoutSmoothing = map (rpmVal, 0, 13000, 1, 255);  
   TachometerRemapedWithoutSmoothing = constrain(TachometerRemapedWithoutSmoothing, 1, 255);
   Serial1.print("p1.pic=");  
   Serial1.print(TachometerRemapedWithoutSmoothing); 
   Serial1.write(0xff);
   Serial1.write(0xff);
   Serial1.write(0xff);


   if (rpmVal>=9500 && flag==0 && digitalRead(butt)==LOW)
    {
      flag=1;
      digitalWrite(upbutton,LOW);
      delay(100);
      digitalWrite(upbutton, HIGH);
      delay(50);
    }   
    if (rpmVal<8250)
    {
    flag=0;
    }

   
   if(rpmVal>3500 && rpmVal<4500)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      digitalWrite(led9,LOW);
      digitalWrite(led10,LOW);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>4500 && rpmVal<6000)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      digitalWrite(led9,LOW);
      digitalWrite(led10,LOW);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>6000 && rpmVal<7000)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,LOW);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      digitalWrite(led9,LOW);
      digitalWrite(led10,LOW);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>7000 && rpmVal<8000)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,LOW);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      digitalWrite(led9,LOW);
      digitalWrite(led10,LOW);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>8000 && rpmVal<8500)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,LOW);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      digitalWrite(led9,LOW);
      digitalWrite(led10,LOW);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>8500 && rpmVal<9000)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,LOW);
      digitalWrite(led8,LOW);
      digitalWrite(led9,LOW);
      digitalWrite(led10,LOW);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>9000 && rpmVal<9500)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,LOW);
      digitalWrite(led9,LOW);
      digitalWrite(led10,LOW);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>9500 && rpmVal<10000)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,HIGH);
      digitalWrite(led9,LOW);
      digitalWrite(led10,LOW);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>10000 && rpmVal<10500)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,HIGH);
      digitalWrite(led9,HIGH);
      digitalWrite(led10,LOW);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>10500 && rpmVal<11000)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,HIGH);
      digitalWrite(led9,HIGH);
      digitalWrite(led10,HIGH);
      digitalWrite(led11,LOW);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>11000 && rpmVal<11500)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,HIGH);
      digitalWrite(led9,HIGH);
      digitalWrite(led10,HIGH);
      digitalWrite(led11,HIGH);
      digitalWrite(led12,LOW);
    }
    if(rpmVal>11500)
    {
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      digitalWrite(led4,HIGH);
      digitalWrite(led5,HIGH);
      digitalWrite(led6,HIGH);
      digitalWrite(led7,HIGH);
      digitalWrite(led8,HIGH);
      digitalWrite(led9,HIGH);
      digitalWrite(led10,HIGH);
      digitalWrite(led11,HIGH);
      digitalWrite(led12,HIGH);
    }
  }

void printFrame2(CAN_FRAME &frame) 
     {
       ctsVal=(frame.data.bytes[5]*256+frame.data.bytes[4])*0.1;
       cts.setValue(ctsVal);
     }
void printFrame3(CAN_FRAME &frame) 
  {     
   bpsVal=(frame.data.bytes[7]*256+frame.data.bytes[6])*0.001;
   bps.setValue(bpsVal*10);
   bpsVal=constrain(bpsVal,0.45,4.6);
   int bpsMapped=map(bpsVal,0.45,4.6,0,100);
   bpsMapped=constrain(bpsMapped,0,100);
   p2.setValue(100-(bpsVal*10));
  }
