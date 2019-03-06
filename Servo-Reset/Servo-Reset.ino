#include <Servo.h>
Servo servo[4];
int pos = 90;

void setup() {
  // put your setup code here, to run once:
  servo[0].attach(3);
  servo[1].attach(5);
  servo[2].attach(6);
  servo[3].attach(9);

  for (int i = 0; i < 4; i++)
  {
    servo[i].write(pos);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
