// Libraries Included
#include <Servo.h>
#define SERVO_SPEED 5
// Initialise Global Variables
Servo servo[4]; // Initialise 4 servo objects
int pos[4]; // Initialise an array of position integers
long randNum[4];

int pos2[8];
long randNum2[8];

void setup() {
  // Attach each of the 4 servos
  Serial.begin(9600);
  servo[0].attach(3); // Servos attached to pin 3, 4, 5, 6
  servo[1].attach(5);
  servo[2].attach(6);
  servo[3].attach(9);

  randomSeed(analogRead(0));
}
void loop() {
  ////////////////////////////////////////////////////
  // THIS MOVES ALL THE ARMS SIMULTANEOUSLY AT RANDOM
  static unsigned long servo_time;
  if ((millis() - servo_time) >= SERVO_SPEED) {
    servo_time = millis(); // save time reference for next position update

    for (int i = 0; i < 4; i++)
    {
      randNum[i] = random(90, 180);
      pos[i] = randNum[i];

      if (pos[i] > servo[i].read())
        servo[i].write(servo[i].read() + 1);
      else if (pos[i] < servo[i].read())
        servo[i].write(servo[i].read() - 1);
      }
  }
  /////////////////////////////////////////////////
}