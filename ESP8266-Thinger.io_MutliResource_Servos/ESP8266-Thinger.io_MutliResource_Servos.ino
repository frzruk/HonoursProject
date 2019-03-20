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
#define MAX_DEGREES 180
#define MIN_DEGREES 0

/** CLASS INSTANCE CREATION **/
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); // Creation of Thinger
Servo servo[8]; // Creation of an array of 4 servos

/** GLOBAL VARIABLES **/
uint8_t fbMessenger = 0; // Number of Messenger notifications
uint8_t whatsApp = 0; // Number of WhatsApp notifications
uint8_t insta = 0; // Number of Instagram notifications
uint8_t twitter = 0; // Number of Twitter notifications
uint8_t texts = 0; // Number of texts
uint8_t facebook = 0; // Number of Facebook notifications
uint8_t snap = 0; // Number of Snapchat notifications
uint8_t email = 0; // Number of emails

void setup() {
  Serial.begin(115200); // Open the Serial Channel for debug and testing purposes

  thing.add_wifi(SSID, SSID_PASSWORD); // Connect the board to WiFi
  servo[0].attach(16); // Attach the first servo to pin 16

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
    handleServos(0, fbMessenger, 15); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("WhatsApp Notifications - "); // Print WhatsApp Notifications
    Serial.println(whatsApp);
    handleServos(1, whatsApp, 10); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Instagram Notifications - "); // Print Instagram Messenger notifications
    Serial.println(insta);
    handleServos(2, insta, 10); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Twitter Notifications - "); // Print Twitter notifications
    Serial.println(twitter);
    handleServos(3, twitter, 10); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Text Message Notifications - "); // Text Message notifications
    Serial.println(texts);
    handleServos(4, texts, 10); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Facebook Notifications - "); // Print Facebook notifications
    Serial.println(facebook);
    handleServos(5, facebook, 10); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Snapchat Notifications - "); // Print Snapchat notifications
    Serial.println(snap);
    handleServos(6, snap, 10); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Email Notifications - "); // Print Email notifications
    Serial.println(email);
    handleServos(7, email, 10); // Move the servos (ServoNum, Notification Count, Degrees to move)
  };
}

void handleServos(int servoNum, int notificationNum, int mult) {
  if (servo[servoNum].read() < MAX_DEGREES)
    servo[servoNum].write(notificationNum * mult); // Move servo a multiplication of degrees
  else if (servo[servoNum].read() >= MAX_DEGREES) {
    servo[servoNum].write((MAX_DEGREES - MIN_DEGREES) / 2 );
    delay(1000);
    servo[servoNum].write(MAX_DEGREES);
  }
}

void loop() {
  thing.handle();
}
