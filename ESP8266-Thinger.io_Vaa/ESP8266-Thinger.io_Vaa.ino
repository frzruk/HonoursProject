#define _DEBUG_ // Used to see DEBUG info in the Serial Monitor
/** INCLUDE LIBRARIES **/
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <Servo.h>

/** DEFINITIONS **/
#define USERNAME "frzruk" // Thinger Username
#define DEVICE_ID "esp8266_huzzah" // Thinger Device ID
#define DEVICE_CREDENTIAL "5tFfA#zZbN$%" // Key to Authenticate to Thinger
#define SSID "StudentResidences" // SSID of the WiFi
#define SSID_PASSWORD "" // Password of the WiFi

/** CLASS INSTANCE CREATION **/
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); // Creation of thinger class
Servo servo[8]; // Creation of Servos

/** GLOBAL VARIABLES **/
uint8_t fbMessenger = 0; // Number of Messenger notifications (%Msgr in Tasker)
uint8_t whatsApp = 0; // Number of WhatsApp notifications (%Whts in Tasker)
uint8_t insta = 0; // Number of Instagram notifications (%Inst in Tasker)
uint8_t twitter = 0; // Number of Twitter notifications (%Twit in Tasker)
uint8_t texts = 0; // Number of Text notifications (%Text in Tasker)
uint8_t facebook = 0; // Number of Facebook notifications (%Face in Tasker)
uint8_t snap = 0; // Number of Snapchat notifications (%Snap in Tasker)
uint8_t email = 0; // Number of Email notifications (%Emai in Tasker)


void setup() {
  Serial.begin(115200); // Open the Serial Channel for debug and testing purposes
  
  /** Attach Servos **/
  // Dont use 2
  servo[0].attach(4); // Attach the first servo to pin 16

  thing.add_wifi(SSID, SSID_PASSWORD); // Connect the board to WiFi

  thing["nots"] << [] (pson & in) { // The resource "nots" is an input resource, as marked by <<
    /** Recieve input resources **/
    fbMessenger = in["Messenger"]; // Get the input of the number of Facebook Messenger notifications
/*    whatsApp = in["WhatsApp"]; // Get the input of the number of WhatsApp notifications
    insta = in["Instagram"]; // Get the input of the number of Instagram notifications
    twitter = in["Twitter"]; // Get the input of the number of Twitter notifications
    texts = in["Texts"]; // Get the input of the number of Text Message notifications
    facebook = in["Facebook"]; // Get the input of the number of Facebook notifications
    snap = in["Snapchat"]; // Get the input of the number of Snapchat notifications
    email = in["Email"]; // Get the input of the number of Gmail notifications*/

    Serial.print("Messenger Notifications - "); // Print Facebook Messenger notifications
    Serial.println(fbMessenger);
   /* Serial.print("WhatsApp Notifications - "); // Print WhatsApp Notifications
    Serial.println(whatsApp);
    Serial.print("Instagram Notifications - "); // Print Instagram Messenger notifications
    Serial.println(insta);
    Serial.print("Twitter Notifications - "); // Print Twitter notifications
    Serial.println(twitter);    
    Serial.print("Text Message Notifications - "); // Text Message notifications
    Serial.println(texts);
    Serial.print("Facebook Notifications - "); // Print Facebook notifications
    Serial.println(facebook);    
    Serial.print("Snapchat Notifications - "); // Print Snapchat notifications
    Serial.println(snap);
    Serial.print("Email Notifications - "); // Print Email notifications*/

    servo[0].write(fbMessenger*5);
  };
}

void loop() {
  thing.handle();
}
