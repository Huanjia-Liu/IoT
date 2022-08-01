import socket
from datetime import datetime
import sys

class UDP_center:

    def __init__(self, ip, port):
        self.port = port            #Set server's port
        self.ip = ip
        
    #For environment client
    def client_en(self,message):
        UDP_IP = self.ip
        UDP_Port = self.port

        binary_message = message.encode('ascii')


        clientSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        clientSock.bind(('',8020))

        try:
            clientSock.sendto(binary_message,(UDP_IP,UDP_Port))        
        except RuntimeError:
            print(f"error: {RuntimeError}")
        
        got = False

        while(got != True):
            print('waiting')
            message,address = clientSock.recvfrom(512)
            got = True
        return message.decode('utf-8')
    #For application client
    def client_light(self,message):
        UDP_IP = self.ip
        UDP_Port = self.port
        binary_message = message.encode('ascii')


        clientSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        clientSock.bind(('',8020))

        try:
            clientSock.sendto(binary_message,(UDP_IP,UDP_Port))        
        except RuntimeError:
            print(f"error: {RuntimeError}")    






