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
ThingerESP8266 thing(USERNAME,DEVICE_ID,DEVICE_CREDENTIAL); // Create Thinger instance passing in user + device credentials
Servo myServo; // Create servo instance

// Define global variables
int servoPos = 0; // Position value for the servo
int notificationCount = 0; // Count the number of notifications

void setup() {
  Serial.begin(115200);
  // Initialise everything needed in here
  thing.add_wifi(SSID,SSID_PASSWORD); // Connect to the WiFi
  Serial.println("Connected?");
  myServo.attach(2);

  // Thinger.io resource control
  // inputs use << pointing to the resource name
/*  thing["servo"] << [](pson& in){ //inside instance of thing, create var "servo" that reads from input
    myServo.write(in); // write this position as the servo position
  };*/

  thing["notificationCount"] << [](pson&in) {
    notificationCount = in;
    Serial.println(notificationCount);
  };
}

void loop() {
  //Serial.println(notificationCount);
  thing.handle(); // Updates the instance based on Thinger.io
  
}
