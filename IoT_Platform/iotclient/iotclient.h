#include"Arduino.h"
#include "WiFiUdp.h"

class iotclient
{
  private:
    char* server_ip;
    int server_port;
    
  public:
    iotclient(char* ip, int port);
    void Udp_Server(WiFiUDP Reciver);
    void wifi_connect(const char* ssid,const char* psw);
    void control_center(char* udp_words);
};
