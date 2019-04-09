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
Servo servo[4]; // Creation of an array of 8 servos

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
  //for(int i = 0; i < 8; i++) {
    //servoReset(i); }

  thing.add_wifi(SSID, SSID_PASSWORD); // Connect the board to WiFi
  servo[0].attach(4); // Attach the first servo to pin 4
  servo[1].attach(5); // Attach the first servo to pin 4
  servo[2].attach(2); // Attach the first servo to pin 4
  servo[3].attach(16); // Attach the first servo to pin 4
//  servo[4].attach(14); // Attach the first servo to pin 4
//  servo[5].attach(15); // Attach the first servo to pin 4
//  servo[6].attach(13); // Attach the first servo to pin 4
//  servo[7].attach(12); // Attach the first servo to pin 4



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
    handleServos(1, whatsApp, 15); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Instagram Notifications - "); // Print Instagram Messenger notifications
    Serial.println(insta);
    handleServos(2, insta, 15); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Twitter Notifications - "); // Print Twitter notifications
    Serial.println(twitter);
    handleServos(3, twitter, 15); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Text Message Notifications - "); // Text Message notifications
    Serial.println(texts);
 //   handleServos(4, texts, 15); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Facebook Notifications - "); // Print Facebook notifications
    Serial.println(facebook);
//    handleServos(5, facebook, 15); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Snapchat Notifications - "); // Print Snapchat notifications
    Serial.println(snap);
//    handleServos(6, snap, 15); // Move the servos (ServoNum, Notification Count, Degrees to move)

    Serial.print("Email Notifications - "); // Print Email notifications
    Serial.println(email);
//    handleServos(7, email, 15); // Move the servos (ServoNum, Notification Count, Degrees to move)
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

void servoReset(int servoNum) {
  servo[servoNum].write(0);
}

void loop() {
  thing.handle();
  delay(1);
}
