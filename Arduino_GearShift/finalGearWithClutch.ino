#define ushiftb 2
#define dshiftb 4
#define slowb 5
#define launchb 3
#define ushiftv 8
#define dshiftv 7
#define clutch 6

#define slowv 9
#define cut 10
int c=0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ushiftb,INPUT_PULLUP);
  pinMode(dshiftb,INPUT_PULLUP);
  pinMode(launchb,INPUT_PULLUP);
  pinMode(slowb,INPUT_PULLUP);
  pinMode(cut,OUTPUT);
  pinMode(ushiftv,OUTPUT);
  digitalWrite(ushiftv,LOW);
  pinMode(dshiftv,OUTPUT);
  digitalWrite(dshiftv,LOW);
  pinMode(clutch,OUTPUT);
  digitalWrite(clutch,LOW);
  pinMode(slowv,OUTPUT);
  digitalWrite(slowv,LOW);
  digitalWrite(cut,LOW);
}


void quick(){
if((digitalRead(slowb)!=LOW or digitalRead(launchb)==LOW) and digitalRead(dshiftb)==LOW)
dshift();
 else if((digitalRead(launchb)==LOW or digitalRead(slowb)!=LOW) and digitalRead(dshiftb)!=LOW){
digitalWrite(clutch,HIGH);
delay(20);}
if(digitalRead(launchb)!=LOW){
digitalWrite(slowv,HIGH);
delay(20);
digitalWrite(clutch,LOW);
delay(70);
digitalWrite(slowv,LOW);
}
else
quick();
}


void slow(){
 
if((digitalRead(slowb)==LOW or digitalRead(launchb)!=LOW) and digitalRead(dshiftb)!=LOW){
digitalWrite(clutch,HIGH);
delay(10);}
else if((digitalRead(slowb)==LOW or digitalRead(launchb)!=LOW) and digitalRead(dshiftb)==LOW)
dshift();
if(digitalRead(slowb)!=LOW){
  delay(20);
  digitalWrite(clutch,LOW);
}
else{
  slow();
} 
}



void ushift(){
  
  digitalWrite(clutch,HIGH);
  delay(150);
  digitalWrite(ushiftv,HIGH);
  delay(60);
  digitalWrite(cut,HIGH);
  delay(90);
  digitalWrite(ushiftv,LOW);
  delay(5);
  digitalWrite(cut,LOW); 
  delay(5);
  digitalWrite(slowv,HIGH);
  delay(5);
  digitalWrite(clutch,LOW);
  delay(75);
  digitalWrite(slowv,LOW);
  delay(25);
  
  }

void dshift(){
  if((digitalRead(launchb)==LOW or digitalRead(slowb)==LOW )and digitalRead(dshiftb)==LOW)
  {
     delay(40);
  digitalWrite(dshiftv,HIGH);
  delay(70);
  digitalWrite(dshiftv,LOW);
  delay(75);
  }
  if(digitalRead(dshiftb)==LOW and (digitalRead(slowb)!=LOW or digitalRead(launchb)!=LOW)){  
  digitalWrite(clutch,HIGH);
  delay(40);
  digitalWrite(dshiftv,HIGH);
  delay(70);
  digitalWrite(dshiftv,LOW);
  delay(75);
  digitalWrite(slowv,HIGH);
  delay(15);
  digitalWrite(clutch,LOW);
  delay(75);
  digitalWrite(slowv,LOW);
  delay(25);
  }
  }

void loop(){
    //if(digitalRead(dshiftb)==LOW or digitalRead(slowb)==LOW or digitalRead(launchb)==LOW)
  if(digitalRead(dshiftb)==LOW){
     delay(20);
     dshift();}
  else if(digitalRead(slowb)==LOW){
    if(digitalRead(slowb)==LOW){
    delay(20);
    slow();}}
  else if(digitalRead(launchb)==LOW){
   if(digitalRead(launchb)==LOW){
    delay(20);
    quick();}}
  else if(digitalRead(ushiftb)==LOW){
    if(digitalRead(ushiftb)==LOW){
    delay(20);
    ushift();}}
}
