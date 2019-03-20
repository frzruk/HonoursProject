// Include Libraries
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <Servo.h>


// Definitions for constants
#define USERNAME "frzruk" // Thinger.io Username
#define DEVICE_ID "esp8266_huzzah" // Device name used on Thinger.io
#define DEVICE_CREDENTIAL "5tFfA#zZbN$%" // Key to authenticate with server
#define SSID "StudentResidences" // WiFi connection name
#define SSID_PASSWORD "" // Wifi Password

// Create instances of classes
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); // Create Thinger instance passing in user + device credentials
Servo myServo; // Create servo instance

// Define global variables
int servoPos = 0; // Position value for the servo
int notificationCount = 0; // Count the number of notifications
int messenger = 0; // Number of Messenger notifications
int whatsApp = 0; // Number of WhatsApp notifications

void setup() {
  // Initialise everything needed in here
  Serial.begin(115200); // Open Serial bus for communication
  thing.add_wifi(SSID, SSID_PASSWORD); // Connect to the WiFi
  Serial.println("Connected?");
  myServo.attach(2); // Attach the servo to pin 2

  // Thinger.io resource control
  // inputs use << pointing to the resource name
  /*  thing["servo"] << [](pson& in){ //inside instance of thing, create var "servo" that reads from input
      myServo.write(in); // write this position as the servo position
    };*/

  thing["notificationCount"] << [](pson & in) {
    messenger = in["Messenger"]; // Get input data for Messenger from Thinger
    whatsApp = in["WhatsApp"]; // Get input data for WhatsApp from Thinger

    Serial.print("Messenger Notifications - ");
    Serial.println(messenger);
    Serial.print("WhatsApp Notifications - ");
    Serial.println(whatsApp);
  };
}

void loop() {
  thing.handle(); // Updates the instance based on Thinger.io

}
