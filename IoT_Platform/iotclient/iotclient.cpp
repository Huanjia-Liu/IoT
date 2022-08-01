#include"Arduino.h"
#include"math.h"
#include "ESP8266WiFi.h"
#include"iotclient.h"


iotclient::iotclient(char* ip, int port)
{
  server_ip =  ip;  
  server_port = port;
}



void iotclient::wifi_connect(const char* ss,const char* psw){
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println(ss);
  WiFi.begin(ss,psw);
  Serial.print("Connecting");
  while( WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print(WiFi.localIP());
  Serial.println("dddd");

}   



void iotclient::Udp_Server(WiFiUDP Socket){
   int sum = 0;
   while(sum != 500)
   {
      char* packetBuffer = (char*) malloc (2);
      int packetSize = Socket.parsePacket();
      
      if (packetSize!=0)
      {
        
        Socket.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    
        Serial.println(packetBuffer);
        control_center(packetBuffer);


        
     
      }
      free(packetBuffer);
      sum ++;
   }
}

void iotclient::control_center(char* udp_words)
{
  char temp[3] = "00";
  temp[0] = udp_words[0];
  temp[1] = udp_words[1];
  if(strcmp(temp, "on")==0)
  {
    digitalWrite(D1,HIGH);
  } 
  if(strcmp(temp, "of")==0)
  {
    digitalWrite(D1,LOW);
  } 
  
 
  
}
