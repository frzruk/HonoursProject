#define _DEBUG_ // Used to see DEBUG info in the Serial Monitor
/** INCLUDE LIBRARIES **/
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

/** DEFINITIONS **/
#define USERNAME "frzruk" // Thinger Username
#define DEVICE_ID "esp8266_huzzah" // Thinger Device ID
#define DEVICE_CREDENTIAL "5tFfA#zZbN$%" // Key to Authenticate to Thinger
#define SSID "StudentResidences" // SSID of the WiFi
#define SSID_PASSWORD "" // Password of the WiFi
#define SERVOMIN 120 // Minimum pulse length of the servo
#define SERVOMAX 610 // Maximum pulse length of the servo

/** CLASS INSTANCE CREATION **/
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); // Creation of Thinger
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); // Creation of PWMDRiver

/** GLOBAL VARIABLES **/
int fbMessenger = 0; // Number of Messenger notifications
int prevFBMessenger = 0;
int whatsApp = 0; // Number of WhatsApp notifications
int servoNum = 4; // Define the number of servos
int pulseLength;
long degs = 0;

void setup() {
  Serial.begin(115200); // Open the Serial Channel for debug and testing purposes
  pwm.begin(); // Open the communication channel with the PWM Driver
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  delay(10);

  thing.add_wifi(SSID, SSID_PASSWORD); // Connect the board to WiFi
  pulseLength = map(degs, 0 , 180, SERVOMIN, SERVOMAX);

  thing["nots"] << [] (pson & in) { // The resource "nots" is an input resource, as marked by <<
    /** Recieve input resources **/
    fbMessenger = in["Messenger"]; // Get the input of the number of Facebook Messenger notifications
    whatsApp = in["WhatsApp"]; // Get the input of the number of WhatsApp notifications
    /*    insta = in["Instagram"]; // Get the input of the number of Instagram notifications
        twitter = in["Twitter"]; // Get the input of the number of Twitter notifications
        texts = in["Texts"]; // Get the input of the number of Text Message notifications
        facebook = in["Facebook"]; // Get the input of the number of Facebook notifications
        snap = in["Snapchat"]; // Get the input of the number of Snapchat notifications
        email = in["Email"]; // Get the input of the number of Gmail notifications*/

    Serial.print("Messenger Notifications - "); // Print Facebook Messenger notifications
    Serial.println(fbMessenger);

    if(prevFBMessenger != fbMessenger)
    {
      pwm.setPWM(0, 0, map(5, 0, 180, SERVOMIN, SERVOMAX));
      prevFBMessenger = fbMessenger;
    }

    Serial.print("WhatsApp Notifications - "); // Print WhatsApp Notifications
    Serial.println(whatsApp);
    /* Serial.print("Instagram Notifications - "); // Print Instagram Messenger notifications
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
  };
}

void loop() {
  thing.handle();
}

/** you can use this function if you'd like to set the pulse length in seconds **/
/* e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise! **/
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;

  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  Serial.print(pulselength); Serial.println(" us per period");
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit");
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}
