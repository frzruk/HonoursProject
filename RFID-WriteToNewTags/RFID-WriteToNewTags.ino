/*
   Writing Data received from Thinger to the next RFID Card presented
   ------------------------------------------------------------------
   Signal     |  MFRC522  |  HUZZAH
   ---------------------------------
   RST/Reset  |  RST      |   3
   SPI SS     |  SDA(SS)  |   4
   SPI MOSI   |  MOSI     |   13
   SPI MISO   |  MISO     |   12
   SPI SCK    |  SCK      |   14
   -------------------------------------------------------------------
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         3           // Configurable, see typical pin layout above
#define SS_PIN          4          // Configurable, see typical pin layout above

const int R_PIN = 12;
const int G_PIN = 13;
const int B_PIN = 15;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card

  // Prepare the key (used both as key A and as key B)
  // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("Scan a MIFARE Classic PICC to demonstrate read and write."));
  Serial.print(F("Using key (for A and B):"));
  dump_byte_array(key.keyByte, MFRC522::MF_KEY_SIZE);
  Serial.println();

  Serial.println(F("BEWARE: Data will be written to the PICC, in sector #1"));

  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
}

/**
   Main loop.
*/
void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
    return;

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

  // Show some details of the PICC (that is: the tag/card)
  Serial.print(F("Card UID:"));
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println();
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

  // Check for compatibility
  if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
          &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
          &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("This sample only works with MIFARE Classic cards."));
    return;
  }

  // In this sample we use the second sector,
  // that is: sector #1, covering block #4 up to and including block #7
  byte sector         = 1;
  byte blockAddr      = 4;
  byte dataBlock[]    = {
    0x01, 0x02, 0x03, 0x04, //  1,  2,   3,  4,
    0x05, 0x06, 0x07, 0x08, //  5,  6,   7,  8,
    0x09, 0x0a, 0xff, 0x0b, //  9, 10, 255, 11,
    0x0c, 0x0d, 0x0e, 0x0f  // 12, 13, 14, 15
  };
  byte trailerBlock   = 7;
  MFRC522::StatusCode status;
  byte buffer[18];
  byte size = sizeof(buffer);

  // Authenticate using key A
  Serial.println(F("Authenticating using key A..."));
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Show the whole sector as it currently is
  Serial.println(F("Current data in sector:"));
  mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
  Serial.println();

  // Read data from the block
  Serial.print(F("Reading data from block ")); Serial.print(blockAddr);
  Serial.println(F(" ..."));
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  Serial.print(F("Data in block ")); Serial.print(blockAddr); Serial.println(F(":"));
  dump_byte_array(buffer, 16); Serial.println();
  Serial.println();

  // Authenticate using key B
  Serial.println(F("Authenticating again using key B..."));
  status = (MFRC522::StatusCode) mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Write data to the block
  Serial.print(F("Writing data into block ")); Serial.print(blockAddr);
  Serial.println(F(" ..."));
  dump_byte_array(dataBlock, 16); Serial.println();
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(blockAddr, dataBlock, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  Serial.println();

  // Read data from the block (again, should now be what we have written)
  Serial.print(F("Reading data from block ")); Serial.print(blockAddr);
  Serial.println(F(" ..."));
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }
  Serial.print(F("Data in block ")); Serial.print(blockAddr); Serial.println(F(":"));
  dump_byte_array(buffer, 16); Serial.println();

  // Check that data in block is what we have written
  // by counting the number of bytes that are equal
  Serial.println(F("Checking result..."));
  byte count = 0;
  for (byte i = 0; i < 16; i++) {
    // Compare buffer (= what we've read) with dataBlock (= what we've written)
    if (buffer[i] == dataBlock[i])
      count++;
  }
  Serial.print(F("Number of bytes that match = ")); Serial.println(count);
  if (count == 16) {
    Serial.println(F("Success :-)"));
  } else {
    Serial.println(F("Failure, no match :-("));
    Serial.println(F("  perhaps the write didn't work properly..."));
  }
  Serial.println();

  // Dump the sector data
  Serial.println(F("Current data in sector:"));
  mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
  Serial.println();

  // Halt PICC
  mfrc522.PICC_HaltA();
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();

  mainColors();
  showSpectrum();
}

/**
   Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}


// Here's the mainColors() function we've written.

// This function displays the eight "main" colors that the RGB LED
// can produce. If you'd like to use one of these colors in your
// own sketch, you cancopy and paste that section into your code.

void mainColors()
{
  // Off (all LEDs off):

  digitalWrite(R_PIN, LOW);
  digitalWrite(G_PIN, LOW);
  digitalWrite(B_PIN, LOW);

  delay(1000);

  // Red (turn just the red LED on):

  digitalWrite(R_PIN, HIGH);
  digitalWrite(G_PIN, LOW);
  digitalWrite(B_PIN, LOW);

  delay(1000);

  // Green (turn just the green LED on):

  digitalWrite(R_PIN, LOW);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(B_PIN, LOW);

  delay(1000);

  // Blue (turn just the blue LED on):

  digitalWrite(R_PIN, LOW);
  digitalWrite(G_PIN, LOW);
  digitalWrite(B_PIN, HIGH);

  delay(1000);

  // Yellow (turn red and green on):

  digitalWrite(R_PIN, HIGH);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(B_PIN, LOW);

  delay(1000);

  // Cyan (turn green and blue on):

  digitalWrite(R_PIN, LOW);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(B_PIN, HIGH);

  delay(1000);

  // Purple (turn red and blue on):

  digitalWrite(R_PIN, HIGH);
  digitalWrite(G_PIN, LOW);
  digitalWrite(B_PIN, HIGH);

  delay(1000);

  // White (turn all the LEDs on):

  digitalWrite(R_PIN, HIGH);
  digitalWrite(G_PIN, HIGH);
  digitalWrite(B_PIN, HIGH);

  delay(1000);
}

// Below are two more functions we've written,
// showSpectrum() and showRGB().

// showRGB() displays a single color on the RGB LED.
// You call showRGB() with the number of a color you want
// to display.

// showSpectrum() steps through all the colors of the RGB LED,
// displaying a rainbow. showSpectrum() actually calls showRGB()
// over and over to do this.

// We'll often break tasks down into individual functions like
// this, which makes your sketches easier to follow, and once
// you have a handy function, you can reuse it in your other
// programs.


// showSpectrum()

// This function steps through all the colors of the RGB LED.
// It does this by stepping a variable from 0 to 768 (the total
// number of colors), and repeatedly calling showRGB() to display
// the individual colors.

// In this function, we're using a "for() loop" to step a variable
// from one value to another, and perform a set of instructions
// for each step. For() loops are a very handy way to get numbers
// to count up or down.

// Every for() loop has three statements separated by semicolons:

//   1. Something to do before starting

//   2. A test to perform; as long as it's true,
//      it will keep looping

//   3. Something to do after each loop (usually
//      increase a variable)

// For the for() loop below, these are the three statements:

//   1. x = 0;     Before starting, make x = 0.

//   2. x < 768;   While x is less than 768, run the
//                 following code.

//   3. x++        Putting "++" after a variable means
//                 "add one to it". (You can also use "x = x + 1")

// Every time you go through the loop, the statements following
// the loop (those within the brackets) will run.

// And when the test in statement 2 is finally false, the sketch
// will continue.


void showSpectrum()
{
  int x;  // define an integer variable called "x"

  // Now we'll use a for() loop to make x count from 0 to 767
  // (Note that there's no semicolon after this line!
  // That's because the for() loop will repeat the next
  // "statement", which in this case is everything within
  // the following brackets {} )

  for (x = 0; x < 768; x++)

    // Each time we loop (with a new value of x), do the following:

  {
    showRGB(x);  // Call RGBspectrum() with our new x
    delay(10);   // Delay for 10 ms (1/100th of a second)
  }
}


// showRGB()

// This function translates a number between 0 and 767 into a
// specific color on the RGB LED. If you have this number count
// through the whole range (0 to 767), the LED will smoothly
// change color through the entire spectrum.

// The "base" numbers are:
// 0   = pure red
// 255 = pure green
// 511 = pure blue
// 767 = pure red (again)

// Numbers between the above colors will create blends. For
// example, 640 is midway between 512 (pure blue) and 767
// (pure red). It will give you a 50/50 mix of blue and red,
// resulting in purple.

// If you count up from 0 to 767 and pass that number to this
// function, the LED will smoothly fade between all the colors.
// (Because it starts and ends on pure red, you can start over
// at 0 without any break in the spectrum).


void showRGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;

  // Here we'll use an "if / else" statement to determine which
  // of the three (R,G,B) zones x falls into. Each of these zones
  // spans 255 because analogWrite() wants a number from 0 to 255.

  // In each of these zones, we'll calculate the brightness
  // for each of the red, green, and blue LEDs within the RGB LED.

  if (color <= 255)          // zone 1
  {
    redIntensity = 255 - color;    // red goes from on to off
    greenIntensity = color;        // green goes from off to on
    blueIntensity = 0;             // blue is always off
  }
  else if (color <= 511)     // zone 2
  {
    redIntensity = 0;                     // red is always off
    greenIntensity = 255 - (color - 256); // green on to off
    blueIntensity = (color - 256);        // blue off to on
  }
  else // color >= 512       // zone 3
  {
    redIntensity = (color - 512);         // red off to on
    greenIntensity = 0;                   // green is always off
    blueIntensity = 255 - (color - 512);  // blue on to off
  }

  // Now that the brightness values have been set, command the LED
  // to those values

  analogWrite(R_PIN, redIntensity);
  analogWrite(B_PIN, blueIntensity);
  analogWrite(G_PIN, greenIntensity);
}
