


#include"fishtank.h"
#include"Arduino.h"
#include"math.h"
#include "ESP8266WiFi.h"

//WiFiUdp Udp;

fishtank::fishtank(byte pin,int R)
{
    rth_pin = pin;
    pinMode(rth_pin,INPUT);
    
    Ri = R;
}   


void fishtank::printtest()
{
    Serial.println(rth_pin);
    
}

float fishtank::temp_rth_get()
{
  int bit_voltage = analogRead(rth_pin);
  
  float real_voltage = 0.0032*bit_voltage;
  //Serial.println(real_voltage);
  float Rth_value = (((3.3/(3.3-real_voltage))-1)*Ri);
  return Rth_value;
}

float fishtank::temp_value_cal(float value)
{
    float temputrue = pow((R_A+R_B*log(value/Ref)+R_C*pow(log(value/Ref),2)+R_D*pow(log(value/Ref),3)),-1);               //fomula from datasheet
    return temputrue-273.15;
}

void fishtank::rth_parameter(float A, float B, float C, float D, float value, float ref)
{
    R_A = A;
    R_B = B;
    R_C = C;
    R_D = D;
    R_Bvalue = value;
    Ref = ref;
}


//wifi connecting
void fishtank::wifi_connect(const char* ss,const char* psw){
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

}   

/****
void wifi_parameter(char ssid,char psw)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(STASSID, STAPSK);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(500);
    }
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
    Serial.printf("UDP server on port %d\n", localPort);
    Udp.begin(localPort);
}
****/
