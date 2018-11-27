// Libraries Included
#include <Servo.h>

// Initialise Global Variables
Servo servo[4];
Servo servo0; // Initialise 4 servo objects
Servo servo1;
Servo servo2;
Servo servo3;
int pos2 = 0;

void setup() {
  // Attach each of the 4 servos
  servo[0].attach(3);
  servo[1].attach(5);
  servo[2].attach(6);
  servo[3].attach(9);
}
void loop() {
  for (pos2 = 0; pos2 <= 180; pos2++) {
    for (int i = 0; i < 4; i++)
      servo[i].write(pos2);
    delay(15);
  }
  for (pos2 = 180; pos2 >= 0; pos2--)
  {
    for (int j = 0; j < 4; j++)
      servo[j].write(pos2);
    delay(15);
  }
}
