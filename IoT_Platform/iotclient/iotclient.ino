

#include "math.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
#include "iotclient.h"
#include "DHTesp.h"


DHTesp dht;
iotclient my_client("192.168.0.4",8020);
const char* ssid = "aceleo2.4";               //wifi ssid and password
const char* password = "liuhuanjia@.";
WiFiUDP Reciver;
//WiFiUDP Sender;


void setup() {
  Serial.begin(115200);

  pinMode(D1,OUTPUT);

  my_client.wifi_connect(ssid,password);
  Reciver.begin(8040);
  // put your setup code here, to run once:
  //my_client.wifi_connect(ssid,password);
  //dht.setup(A0, DHTesp::DHT11);
}




void loop() {

  my_client.Udp_Server(Reciver);
}
