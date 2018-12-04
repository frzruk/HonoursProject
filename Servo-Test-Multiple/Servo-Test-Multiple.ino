// Libraries Included
#include <Servo.h>

// Initialise Global Variables
Servo servo[4];
int pos[4];

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
  Serial.begin(9600);

  //  pinMode(buttonPin, INPUT);

  // Attach each of the servos
  servo[0].attach(A0);
  servo[1].attach(A1);
  servo[2].attach(A1);
  servo[3].attach(A3);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (pos[0] = 150; pos[0] <= 180; pos[0]++) {
    servo[0].write(pos[0]);
    servo[1].write(pos[0]);
    servo[2].write(pos[0]);
    servo[3].write(pos[0]);
    delay(15);
  }
  for (pos[0] = 180; pos[0] >= 150; pos[0]--)
  {
    servo[0].write(pos[0]);
    servo[1].write(pos[0]);
    servo[2].write(pos[0]);
    servo[3].write(pos[0]);
    delay(15);
  }
}


// Get input of followers and following from instagram via "RFID"
//map(var, fromLow, fromHigh, toLow, toHigh)

// Read pos[0]ition of all the servos
//  for (int i = 0; i < 12; i++)
//  {
//    pos[0][i] = servo[i].read();]
//    Serial.println("Servo pos[0]ition:" servo[i]);
//  }
//  buttonState = digitalRead(buttonPin);
//
//  if (buttonState = HIGH) {
//    curFollowers = followers[x];
//    curFollowing = following[x];
//
//    // Pair #1
//    servo[0].write(map(curFollowers, 0, 10000, 30, 60));
//    servo[1].write(map(curFollowing, 0, 10000, 30, 60));
//
//    // Pair #2
//    servo[2].write(pos[0][0]);
//    servo[3].write(pos[0][1]);
//
//    // Pair #3
//    servo[4].write(pos[0][2]);
//    servo[5].write(pos[0][3]);
//
//    // Pair #4
//    servo[6].write(pos[0][4]);
//    servo[7].write(pos[0][5]);
//
//    // Pair #5
//    servo[8].write(pos[0][6]);
//    servo[9].write(pos[0][7]);
//
//    // Pair #6
//    servo[10].write(pos[0][8]);
//    servo[11].write(pos[0][9]);
//
//    x = x+1;
//  }
//  map the number of followers and following to a normalised range of the servos
//    set servo[0] to number of followers
//    set servo[1] to number of following
//    pass the values to the next servos along
