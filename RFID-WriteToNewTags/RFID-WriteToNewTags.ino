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

#define RST_PIN         3          // Configurable, see typical pin layout above
#define SS_PIN          4         // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);		// Initialize serial communications with the PC
  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();			// Init SPI bus
  rfid.PCD_Init();		// Init MFRC522
  rfid.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("This code will check for the presence of a phone's NFC chip."));
  Serial.println(F("It then writes data to a new RFID tag (marble etc.) that's"));
  Serial.println(F("'taken' from social media accounts from the NFC on smartphones"));
}

void loop() {
  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! rfid.PICC_ReadCardSerial()) {
    return;
  }

  // This dumps the Unique ID of the NFC Chip in the phone
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }

  // This dumps the PICC Type of the card
  Serial.print(F(" PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  
  // Start to write data to the new RFID tag in the code below
  byte buffer[34];
  byte block;
  MFRC522::StatusCode status;
  byte len;

  // This block of code gets input from the Serial Monitor
  Serial.setTimeout(20000L); // Wait for 20 seconds till timeout
  Serial.println(F("Type in number of followers, end with #"));
  len = Serial.readBytesUntil('#', (char *) buffer, 30); // This reads the data input into the Serial
  for(byte i = len; i < 30; i++) buffer[i] = ' '; // Pad the rest with spaces

  // Check the authentication of block 1
  block = 1;
  status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(rfid.GetStatusCodeName(status));
    return;
  }
  else Serial.println(F("PCD_Authenticate() success: "));

  
  // Write information to variables and store on new RFID Marble
  //  Each of these need to be written to different blocks on RFID card
  //    Followers
  //    Following
  //    Likes on Posts
  //    Number of Posts
  //    Avg. Colour Makeup of Photos
  //
  // Dump debug info about the card; PICC_HaltA() is automatically called
}
