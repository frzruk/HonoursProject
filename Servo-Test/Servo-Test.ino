// Libraries Included
#include <Servo.h>

// Initialise Global Variables
Servo servo; // Initialise 4 servo objects
int pos = 0; // Initialise an array of position integers

void setup() {  
  // Attach each of the 4 servos
    servo.attach(10); // Servos attached to pin 3, 4, 5, 6
}
void loop() {
  // put your main code here, to run repeatedly:
  for (pos = 0; pos <= 90; pos++) {
    servo.write(pos);
    delay(30);
  }
  for(pos = 0; pos >= 90; pos--)
  {
    servo.write(pos);
    delay(50);
  }
}
