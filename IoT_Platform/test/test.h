#include"Arduino.h"
#include "WiFiUdp.h"

class test
{
  private:
    char* server_ip;
    int server_port;
    
  public:
    test(char* ip, int port);
    char* read_data(byte pin);
    void Udp_Server(WiFiUDP Reciver);
    void wifi_connect(const char* ssid,const char* psw);
    char* uno_center(char* udp_words);
};
