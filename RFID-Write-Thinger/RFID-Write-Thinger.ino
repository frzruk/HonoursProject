/*
 * Writing Data received from Thinger to the next RFID Card presented
 * ------------------------------------------------------------------
 * Signal     |  MFRC522  |  HUZZAH
 * ---------------------------------
 * RST/Reset  |  RST      |   3
 * SPI SS     |  SDA(SS)  |   4
 * SPI MOSI   |  MOSI     |   13
 * SPI MISO   |  MISO     |   12
 * SPI SCK    |  SCK      |   14
 * -------------------------------------------------------------------
 */

// Include Libraries
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

// Define variables
#define RST_PIN 3
#define SS_PIN  4
#define USERNAME "frzruk"
#define DEVICE_ID "esp8266_huzzah"
#define DEVICE_CREDENTIAL "5tFfA#zZbN$%"
#define SSID "FY"
#define SSID_PASSWORD "wifi1212"

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 Instance
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); // Create thinger instance

void setup() {
  Serial.begin(9600); //Opens Serial communication with PC
  SPI.begin(); // Initializes SPI bus
  mfrc522.PCD_Init(); // Initializes the card
  Serial.println(F("Write message to MIFARE PICC"));

  thing.add_wifi(SSID, SSID_PASSWORD);
  Serial.println("connected");
}

void loop() {
  thing.handle();

    thing["led"] << [](pson & in) {
    Serial.println("<NAME>");
    Serial.println((const char*) in["name"]);
    Serial.println("<TIME>");
    Serial.println((const char*) in["time"]);
    Serial.println("<TEXT>");
    Serial.println((const char*) in["text"]);
  };
  
  // Prepare key
  MFRC522::MIFARE_Key key;

  // Check for new cards
  if(! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if(! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Display the UID of the card
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  
  // Display the PICC type
  Serial.print(F(" | PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));

//  Serial.setTimeout(20000L); // Wait for 20 seconds for input
//  Serial.println(F("Type Message here: "));
}
