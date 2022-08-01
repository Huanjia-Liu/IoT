#include <Servo.h>


Servo myservo; // create servo object to control a servo
Servo myservo2;
// twelve servo objects can be created on most boards

int pos = 15; // variable to store the servo position
int pos1 = 135;
int val_6 = 0;
int val_7 = 0;
int val_4 = 0;
int val_5 = 0;
void setup() {
  Serial.begin(115200);
  myservo.attach(9); // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  myservo.write(15);
  myservo2.write(135);
}


int turn_up(int pos)
{
  if(pos > 40)
  {
    pos = 40;
  }
  myservo.write(pos);
  pos += 1;
  return pos;
}


int turn_down(int pos)
{
  if(pos < 5)
  {
    pos = 5;
  }
  myservo.write(pos);
  pos -= 1;
  return pos;
}

int turn_left(int pos)
{
  if(pos <= 85)
  {
    pos = 85;
  }
  myservo2.write(pos);
  pos -= 1;
  return pos;
}

int turn_right(int pos)
{
  if(pos >= 175)
  {
    pos = 175;
  }
  myservo2.write(pos);
  pos += 1;
  return pos;
}




void loop() {
  val_6 = digitalRead(6);
  val_7 = digitalRead(7);
  val_4 = digitalRead(4);
  val_5 = digitalRead(5);

  if(val_6)
  {

    pos = turn_up(pos);

  }
  if(val_7)
  {
    pos = turn_down(pos);
    Serial.println(pos);
  }
  if(val_4)
  {
    pos1 = turn_left(pos1);
  }
  if(val_5)
  {
    pos1 = turn_right(pos1);
  }



  val_6 = 0;
  val_7 = 0;
  val_4 = 0;
  val_5 = 0;
  delay(100);
}
