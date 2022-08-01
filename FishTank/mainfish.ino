#include "fishtank.h"
#include "math.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
#include<pt.h>

WiFiUDP recive;                             //udp recive object
WiFiUDP Udp;                                //udp send object
static int a,b=0;
char modechose[15];
fishtank mytank(A0,10000);                  //fishtank object, which is write in fishtank.h, the resistor is 10K ohm
float rth_value;
float temp;
const char* ssid = "loserleo";               //wifi ssid and password
const char* password = "12345678";
char replyPacket[10]; 
char packetBuffer[15];
static int counter1,counter2;
static int protothread1(struct pt *pt)                  //first thread to recive udp packet
{
  PT_BEGIN(pt);

 

    while(1){

      PT_WAIT_UNTIL(pt, counter2!=500);
    
    int packetSize = recive.parsePacket();
    if (packetSize!=0){
    recive.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

    Serial.println(packetBuffer);
    stringtoint(packetBuffer);
    Serial.println(a);
    Serial.println(b);
    }
    counter2++;
}

  PT_END(pt);
}


static int protothread2(struct pt *pt)                   //second thread to send udp packet(temperture)
{
  PT_BEGIN(pt);
  //Serial.println("fuck2");
 

    rth_value = mytank.temp_rth_get();
    Udp.beginPacket("172.20.10.2",8030);
    temp = mytank.temp_value_cal(rth_value);
    dtostrf(temp,6,2,replyPacket);
    Udp.write(replyPacket);
    //Serial.println(replyPacket);
    Udp.endPacket();
    

  PT_END(pt);
}




  static struct pt pt1, pt2;

void setup() {

    //mytank.rth_parameter();
    pinMode(D1,OUTPUT);                                          //air pump pin
    pinMode(D2,OUTPUT);                                          //water pump pin
    Serial.begin(115200);
    mytank.rth_parameter(3.354016*pow(10,-3),2.56985*pow(10,-4),2.620131*pow(10,-6),6.383091*pow(10,-8),3977,10000);           //thermistor parameter set
    mytank.wifi_connect(ssid,password);
    recive.begin(8040);
    

}

void loop() {
    counter2 = 0;
    protothread2(&pt2);
    protothread1(&pt1); 


    analogWrite(D1,a*10);
    analogWrite(D2,b*10);
 


}
                                     
int stringtoint(char getstring[15]){                                  //trans the string from the udp packet to int
  String tempstring;
  //Serial.println(getstring);
  int counter=0;
  int realnumber[4]={0,0,0,0};
  for(int i=0;i<strlen(getstring);i++){
    if(getstring[i]!=' ')
    {
      tempstring += getstring[i];
    }
    if(getstring[i]== ' ')
    {
      
      realnumber[counter]=tempstring.toInt();
      tempstring="";

      counter++;

    }
  }
  realnumber[3]=tempstring.toInt();
  //Serial.println(realnumber[1]);
  a = realnumber[0];
  b = realnumber[1];
  return realnumber[0];
  
}
