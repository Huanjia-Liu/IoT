from UDP_Server import UDP_center
import time
import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306

from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont


class control_center():
    def __init__(self,mode, command):
        self.en_dic = {"humidity":"hu","pressure":"pr","temperature":"tm"}
        self.light_dic = {"on":"on","off":"of"}
        auth = False
        with open("auth_time.txt","r") as f:
            my_time = float(f.readline())
            if time.time()<my_time:
                if(mode == 1):
                    result = self.environment_udp(command)
                    self.server_disp(result,command)
                elif(mode == 2):
                    self.light_udp(command)
            else:
                self.server_disp("N/A","Auth Error")
        #result = self.environment_udp(command)
        #self.server_disp(result,command)

    
    def environment_udp(self,command):
        mine_udp = UDP_center("192.168.0.106",8040)
        en_string = mine_udp.client_en(self.en_dic[command])
        return en_string

    def light_udp(self,command):
        mine_udp = UDP_center("192.168.0.163",8040)
        en_string = mine_udp.client_light(self.light_dic[command])
        return 


    def daily(self):
        data_list = []
        for i in self.en_dic.values():
            data_list.append(self.environment_udp(i))
            time.sleep(0.5)

        return data_list
    def server_disp(self, result,command):
        RST = 24
        DC = 23
        SPI_PORT = 0
        SPI_DEVICE = 0
        disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)
        disp.begin()
        disp.clear()
        disp.display()
        width = disp.width
        height = disp.height
        padding = 2

        image = Image.new('1', (width, height))
        draw = ImageDraw.Draw(image)
        font = ImageFont.load_default()
        draw.text((padding,padding+5),    command,  font=font, fill=255)
        draw.text((padding+40,padding+20),    result,  font=font, fill=255)
        disp.image(image)
        disp.display()

