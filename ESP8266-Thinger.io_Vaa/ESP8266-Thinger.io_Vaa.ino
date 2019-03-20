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
Servo servo[2]; // Creation of Servos

/** GLOBAL VARIABLES **/
int fbMessenger = 0; // Number of Messenger notifications
int whatsApp = 0; // Number of WhatsApp notifications



void setup() {
  Serial.begin(115200); // Open the Serial Channel for debug and testing purposes
  servo[0].attach(16); // Attach the first servo to pin 16

  thing.add_wifi(SSID, SSID_PASSWORD); // Connect the board to WiFi

  thing["nots"] << [] (pson & in) { // The resource "nots" is an input resource, as marked by <<
    /** Recieve input resources **/
    fbMessenger = in["Messenger"]; // Get the input of the number of Facebook Messenger notifications
    whatsApp = in["WhatsApp"]; // Get the input of the number of WhatsApp notifications
    insta = in["Instagram"]; // Get the input of the number of Instagram notifications
    twitter = in["Twitter"]; // Get the input of the number of Twitter notifications
    texts = in["Texts"]; // Get the input of the number of Text Message notifications
    facebook = in["Facebook"]; // Get the input of the number of Facebook notifications
    snap = in["Snapchat"]; // Get the input of the number of Snapchat notifications
    email = in["Email"]; // Get the input of the number of Gmail notifications

    Serial.print("Messenger Notifications - "); // Print Facebook Messenger notifications
    Serial.println(fbMessenger);
    Serial.print("WhatsApp Notifications - "); // Print WhatsApp Notifications
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
    Serial.print("Email Notifications - "); // Print Email notifications
  };
}

void loop() {
  thing.handle();
}
