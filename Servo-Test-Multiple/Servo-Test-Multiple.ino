// Libraries Included
#include <Servo.h>

// Initialise Global Variables
Servo servo[4]; // Initialise 4 servo objects
int pos[4]; // Initialise an array of position integers
long randNum[8];

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
  for (int i = 0; i < 8; i++)
  {
    if (i % 2) {
      randNum[i] = random(90, 130);
    }
    else {
      randNum[i] = random(130, 180);
    }
  }

  for (int j = 0; j < 4; j++)
  {
    pos[j] = randNum[j * 2];
    for (pos[j] = randNum[j * 2]; pos[j] <= 130; pos[j]++)
    {
      servo[j].write(pos[j]);
      servo[j+1].write(pos[j+1]);
      servo[j+2].write(pos[j+2]);
      servo[j+3].write(pos[j+3]);
      delay(15);
    }
    for (pos[j] = randNum[(j * 2) + 1]; pos[j] >= 90; pos[j]--)
    {
      servo[j].write(pos[j]);   
      servo[j+1].write(pos[j+1]);
      servo[j+2].write(pos[j+2]);
      servo[j+3].write(pos[j+3]);
      delay(15);
    }
  }
}

  //
  //  // put your main code here, to run repeatedly:
  // // Servo 1
  //  for (pos[0] = randNum[0]; pos[0] <= 130; pos[0]++) {
  //    servo[0].write(pos[0]);
  //    delay(15);
  //  }
  //  for(pos[0] = randNum[1]; pos[0] >= 90; pos[0]--)
  //  {
  //    servo[0].write(pos[0]);
  //    delay(15);
  //  }
  //  ///////////////////////////////////////////////
  //   // Servo 2
  // randNum[2] = random(90, 130);
  // Serial.println(randNum[2]);
  // randNum[3] = random(130, 180);
  // Serial.println(randNum[3]);
  // pos[1] = randNum[2];
  //  for (pos[1] = randNum[2]; pos[1] <= 130; pos[1]++) {
  //    servo[1].write(pos[1]);
  //    delay(15);
  //  }
  //  for(pos[1] = randNum[3]; pos[1] >= 90; pos[1]--)
  //  {
  //    servo[1].write(pos[1]);
  //    delay(15);
  //  }
  //  ////////////////////////////////////////////////
  //   // Servo 3
  // randNum[4] = random(90, 130);
  // Serial.println(randNum[4]);
  // randNum[5] = random(130, 180);
  // Serial.println(randNum[5]);
  // pos[2] = randNum[4];
  //  for (pos[2] = randNum[4]; pos[2] <= 130; pos[2]++) {
  //    servo[2].write(pos[2]);
  //    delay(15);
  //  }
  //  for(pos[2] = randNum[5]; pos[2] >= 90; pos[2]--)
  //  {
  //    servo[2].write(pos[2]);
  //    delay(15);
  //  }
  //  ////////////////////////////////////////////////
  //   // Servo 4
  // randNum[6] = random(90, 130);
  // Serial.println(randNum[6]);
  // randNum[7] = random(130, 180);
  // Serial.println(randNum[7]);
  // pos[3] = randNum[6];
  //  for (pos[3] = randNum[6]; pos[3] <= 130; pos[3]++) {
  //    servo[3].write(pos[3]);
  //    delay(15);
  //  }
  //  for(pos[3] = randNum[7]; pos[3] >= 90; pos[3]--)
  //  {
  //    servo[3].write(pos[3]);
  //    delay(15);
  //  }
  //}
