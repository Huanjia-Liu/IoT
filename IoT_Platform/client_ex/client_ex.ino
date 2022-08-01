char mystr[5] = "tp";

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:

}

void loop() {
  //Serial.readBytes(mystr,2);
  Serial.write(mystr,2);
  //Serial.println(mystr);
  delay(5000);
  //if(mystr[0] == 'p'&& mystr[1] == 't')
  //{
  //  Serial.write("re",2);
  //}
  
}
