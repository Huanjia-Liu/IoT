#include"Arduino.h"
#include"math.h"
#include "ESP8266WiFi.h"
#include"test.h"


test::test(char* ip, int port)
{
  server_ip =  ip;  
  server_port = port;
}



void test::wifi_connect(const char* ss,const char* psw){
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

char* test::read_data(byte pin){

  char toUno_buf[5] = "0000";
  char* temp = (char*) malloc (2);

  digitalWrite(pin,HIGH);
  delay(500);
  Serial.readBytes(toUno_buf,5);

  Serial.println(toUno_buf);
  digitalWrite(pin,LOW);
  delay(2000);

  return toUno_buf;
}

void test::Udp_Server(WiFiUDP Socket){
   int sum = 0;
   while(sum != 500)
   {
      char* packetBuffer = (char*) malloc (2);
      
      int packetSize = Socket.parsePacket();
      
      if (packetSize!=0)
      {
        
        Socket.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    
        Serial.println(packetBuffer);
        char* toUno_buf = uno_center(packetBuffer);
        char temp[5] = "0000";
        for(int i =0; i<4;i++)
        {
          temp[i] = toUno_buf[i];
        }

        Socket.beginPacket(server_ip, server_port);
        Serial.println(temp);
        Socket.write(temp);
        
        Socket.endPacket();
      }

      free(packetBuffer);
      sum ++;
   }
}

char* test::uno_center(char* udp_words){
  char temp[3] = "00";
  temp[0] = udp_words[0];
  temp[1] = udp_words[1];
  byte pin = 0;

  if(strcmp(temp, "hu")==0)
  {
    pin = D1;


  }
  if(strcmp(temp, "tm")==0)
  {
    pin = D0;

  }
  if(strcmp(temp, "pr")==0)
  {
    pin = D2;

  }
  char* final_data = read_data(pin);
  return final_data;
  
}
