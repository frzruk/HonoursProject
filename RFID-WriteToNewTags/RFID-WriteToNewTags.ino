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
MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);		// Initialize serial communications with the PC
  while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();			// Init SPI bus
  rfid.PCD_Init();		// Init MFRC522
  rfid.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  Serial.println(F("This code will check for the presence of a phone's NFC chip."));
  Serial.println(F("It then writes data to a new RFID tag (marble etc.) that's"));
  Serial.println(F("'taken' from social media accounts from the NFC on smartphones"));

  // Prepare the key (used both as key A and key B)
  // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  dumpByteArray(key.keyByte, MFRC522::MF_KEY_SIZE);
  Serial.println();
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
  dumpByteArray(rfid.uid.uidByte, rfid.uid.size);

  // This dumps the PICC Type of the card
  Serial.print(F(" PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  
  // Start to write data to the new RFID tag in the code below


  // Write information to variables and store on new RFID Marble
  //  Each of these need to be written to different blocks on RFID card
  //    Followers
  //    Following
  //    Likes on Posts
  //    Number of Posts
  //    Avg. Colour Makeup of Photos
  //
  // Dump debug info about the card; PICC_HaltA() is automatically called

 
 /*
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dumpByteArray(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
}
