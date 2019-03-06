// Libraries Included
#include <Servo.h>
#define SERVO_SPEED1 5
#define SERVO_SPEED2 15
#define SERVO_SPEED3 30
#define SERVO_SPEED4 45
// Initialise Global Variables
Servo servo[4]; // Initialise 4 servo objects
int pos[4] = { 0, 0, 0, 0 }; // Initialise an array of position integers
int buttonPin[5] = {9, 10, 11, 12, 8};
int buttonState[5];
long randNum[4];

long randNum2[8];

void setup() {
  // Attach each of the 4 servos
  Serial.begin(9600);
  // Servos attached to 3,5,6,9 (NANO)
  // Servos attached to 16, 15, 6, 7 (HUZZAH)
  servo[0].attach(7);
  servo[1].attach(5);
  servo[2].attach(3);
  servo[3].attach(6);

  for (int i = 0; i < 4; i++)
  {
    servo[i].write(pos[0]);
  }
  for (int j = 0; j < 5; j++)
  {
    pinMode(buttonPin[j], OUTPUT);
  }

  randomSeed(analogRead(0));
}
void loop() {
  /******************************************/
  /* THIS MOVES ALL THE ARMS SIMULTANEOUSLY AT RANDOM*/
  /*  static unsigned long servo_time;
    if ((millis() - servo_time) >= SERVO_SPEED) {
      servo_time = millis(); // save time reference for next position update

      for (int i = 0; i < 4; i++)
      {
        randNum[i] = random(0 , 90);
        pos[i] = randNum[i];

        if (pos[i] > servo[i].read())
          servo[i].write(servo[i].read() + 1);
        else if (pos[i] < servo[i].read())
          servo[i].write(servo[i].read() - 1);
        }
    }*/
  /*///////////////////////////////////////////////
    // THIS IS THE "IMPORTANT ARM" MOVEMENT*/
  static unsigned long servo_time1;
  static unsigned long servo_time2;
  static unsigned long servo_time3;
  static unsigned long servo_time4;

  for (int k = 0; k < 5; k++)
  {
    buttonState[k] = digitalRead(buttonPin[k]);
  }
  /******************************************/
  if ((millis() - servo_time1) >= SERVO_SPEED1) {
    servo_time1 = millis();

    if (buttonState[0] == HIGH && pos[0] < 91)
    {
      pos[0] += 30; // 3 Steps
      Serial.println(pos[0]);
      delay(200);
    }
  }

  if ((millis() - servo_time2) >= SERVO_SPEED2) {
    servo_time2 = millis();
    if (buttonState[1] == HIGH && pos[1] < 91)
    {
      pos[1] = pos[1] + 15; // 6 Steps
      delay(200);
    }
  }

  if ((millis() - servo_time3) >= SERVO_SPEED3) {
    servo_time3 = millis();
    if (buttonState[2] == HIGH && pos[2] < 91)
    {
      pos[2] = pos[2] + 10; // 9 Steps
      delay(200);
    }
  }

  if ((millis() - servo_time4) >= SERVO_SPEED4) {
    servo_time4 = millis();
    if (buttonState[3] == HIGH && pos[3] < 91)
    {
      pos[3] = pos[3] + 5; // 18 Steps
      delay(200);
    }
  }

  if (buttonState[4] == HIGH)
  {
    for (int x = 0; x < 4; x++)
    {
      pos[x] = 0;
    }
    delay(200);
  }

  for (int i = 0; i < 4; i++)
  {
    if (pos[i] > servo[i].read())
      servo[i].write(servo[i].read() + 1);
    else if (pos[i] < servo[i].read())
      servo[i].write(servo[i].read() - 1);
  }
}
