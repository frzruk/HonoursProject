#define _DEBUG_
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
int potPin = 2;
int val = 0;

// Create instances of classes
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); // Create Thinger instance passing in user + device credentials
Servo servo[2]; // Create servo instances in an array

// Define global variables
int servoPos[2] = {0,0}; // Position value for the servos in an array
int notificationCount = 0; // Count the number of notifications
int messenger = 0; // Number of Messenger notifications
int whatsApp = 0; // Number of WhatsApp notifications

void setup() {
  // Initialise everything needed in here
  Serial.begin(115200); // Open Serial bus for communication
  thing.add_wifi(SSID, SSID_PASSWORD); // Connect to the WiFi
  Serial.println("Connected?");
  servo[0].attach(2); // Attach the servo to pin 2
  servo[1].attach(16); // Attach the servo to pin 16
  // Thinger.io resource control
  // inputs use << pointing to the resource name
  // outputs use >> pointing to the pointing away from the resource name
  // input/output use = next to the resource name

  // BASIC SERVO CONTROL FROM THE API
  /*  thing["servo"] << [](pson& in){ //inside instance of thing, create var "servo" that reads from input
      myServo.write(in); // write this position as the servo position
    };*/
  // END BASIC SERVO CONTROL

  // MULTIPLE VARIABLE INPUTS
  /*thing["notificationCount"] << [](pson & in) {
    messenger = in["Messenger"]; // Get input data for Messenger from Thinger
    whatsApp = in["WhatsApp"]; // Get input data for WhatsApp from Thinger

    Serial.print("Messenger Notifications - ");
    Serial.println(messenger);
    Serial.print("WhatsApp Notifications - ");
    Serial.println(whatsApp);
  };*/
  // END MULTIPLE VARIABLE INPUTS

  // OUTPUT RESOURCES DIDNT WORK
  /*thing["potentiometer"] >> [](pson& out){
    out = analogRead(potPin);
    Serial.println(analogRead(potPin));
  };*/
  // END OUTPUT RESOURCES DIDNT WORK

  // BOTH RESOURCES
 /* thing["in_out"] = [](pson& in, pson& out){
  out["sum"] = (long)in["value1"] + (long)in["value2"];
  out["mult"] = (long)in["value1"] * (long)in["value2"];
  };*/
  // END BOTH RESOURCES

  // MULTIPLE SERVO CONTROL FROM MULTIPLE INPUTS
  thing["servos"] << [](pson& in) { // Get input from Thinger
    messenger = in["Messenger"];
    whatsApp = in["WhatsApp"];

    
    //servo[0].write(messenger*5);// Moves Servo 1 based on Thinger
    //servo[1].write(whatsApp*10);// Moves Servo 2 based on Thinger
  };
  // END MULTIPLE SERVO CONTROL
}

void loop() {
  thing.handle(); // Updates the instance based on Thinger.io
}
