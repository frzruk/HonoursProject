// Libraries Included
#include <Servo.h>

// Initialise Global Variables
Servo servo[12];
int pos[12];
const int buttonPin = 2;
int buttonState = 0;

const int followers[6] = { 299, 182, 258, 620, 508,  632 };
const int following[6] = { 356, 247, 336, 590, 1058, 2100 };
int curFollowers = 0;
int curFollowing = 0;
int x = 0;

/* Instagram Data
    Username    Followers   Following
    a           299         356
    b           182         247
    c           258         336
    d           620         590
    e           508         1058
    f           632         2100
    g           11          14
    h           6001        2276
    i           1505        999
    j           159         232
    k           141         310
    l           92          234
    m           102         108
    n           102         209
    o           168         277
*/

void setup() {
  pinMode(buttonPin, INPUT);
  // Attach each of the servos
  servo[0].attach(A0);
  servo[1].attach(A1);
  servo[2].attach(A1);
  servo[3].attach(A3);
  servo[4].attach(A4);
  servo[5].attach(A5);
  servo[6].attach(3);
  servo[7].attach(5);
  servo[8].attach(6);
  servo[9].attach(9);
  servo[10].attach(10);
  servo[11].attach(11);

  for(int i = 0; i < 12; i++)
    servo[i].write(90);
}
void loop() {
  // Get input of followers and following from instagram via "RFID"
  //map(var, fromLow, fromHigh, toLow, toHigh)

  buttonState = digitalRead(buttonPin);
  if(buttonState = HIGH) {
    curFollowers = followers[x];
    curFollowing = following[x];
    
    for(int i = 0; i < 12; i++)
    {
      pos[i] = servo[i].read();
    }
    // Pair #1
    servo[0].write(map(curFollowers,0,10000,30,60));
    servo[1].write(map(curFollowing,0,10000,30,60));

    // Pair #2
    servo[2].write(pos[0]);
    servo[3].write(pos[1]);

    // Pair #3
    servo[4].write(pos[2]);
    servo[5].write(pos[3]);

    // Pair #4
    servo[6].write(pos[4]);
    servo[7].write(pos[5]);

    // Pair #5
    servo[8].write(pos[6]);
    servo[9].write(pos[7]);

    // Pair #6
    servo[10].write(pos[8]);
    servo[11].write(pos[9]);

    x++;
  }
  //  map the number of followers and following to a normalised range of the servos
  //    set servo[0] to number of followers
  //    set servo[1] to number of following
  //    pass the values to the next servos along
}
