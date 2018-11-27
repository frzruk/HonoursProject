// Libraries Included
#include <Servo.h>

// Initialise Global Variables
Servo servo; // Initialise 4 servo objects
int pos = 0; // Initialise an array of position integers

void setup() {  
  // Attach each of the 4 servos
    servo.attach(9); // Servos attached to pin 3, 4, 5, 6
}
void loop() {
  // put your main code here, to run repeatedly:
  for (pos = 150; pos <= 180; pos++) {
    servo.write(pos);
    delay(15);
  }
  for(pos = 180; pos >= 150; pos--)
  {
    servo.write(pos);
    delay(15);
  }
}
