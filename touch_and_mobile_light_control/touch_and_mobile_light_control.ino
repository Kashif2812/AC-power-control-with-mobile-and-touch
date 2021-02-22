#include "BluetoothSerial.h"
#define light_1 25
#define touch_pin_1 15

BluetoothSerial SerialBT;

const int THRESHOLD = 50 ;

int mode=1;
int btn1=1;

void setup() {
  Serial.begin(115200);
  pinMode(light_1,OUTPUT);
  SerialBT.begin("SMART LIGHTS"); 

}

void button1()
{
  int TOUCH_1_VALUE=0;
  for(int i=0; i< 100; i++)
  {
  TOUCH_1_VALUE += touchRead(touch_pin_1);  
  }
  
  TOUCH_1_VALUE = TOUCH_1_VALUE/100;
  
  if(TOUCH_1_VALUE < THRESHOLD)
  {
    if( mode==1)
    {
      
      btn1=btn1+1;
      btn1=btn1%2;            
    }
    mode=0;
  }
  else
  {
  mode=1;
  }

delay(10);
}

void read_command(){
button1();
  
if (btn1==1)digitalWrite(light_1,HIGH);
else    digitalWrite(light_1,LOW);  

if (SerialBT.available()) {
   char   cmnd=SerialBT.read();
    if (cmnd=='A'){
     btn1=1; 
    }
    if (cmnd=='1'){
      btn1=0;
    }
  }
  delay(20);


}

void loop() { 
read_command();
}
