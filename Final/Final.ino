#define _DEBUG_ // Used to see DEBUG info in the Serial Monitor
#define _DISABLE_TLS_
/** INCLUDE LIBRARIES **/
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <Servo.h>

/** DEFINITIONS **/
#define USERNAME "frzruk" // Thinger Username
#define DEVICE_ID "esp8266_huzzah" // Thinger Device ID
#define DEVICE_CREDENTIAL "5tFfA#zZbN$%" // Key to Authenticate to Thinger
//#define SSID "StudentResidences" // SSID of the WiFi
#define SSID "NOWTV372E1"
#define SSID_PASSWORD "QFRBTWSSYS"
//#define SSID_PASSWORD "" // Password of the WiFi
#define MAX_DEGREES 90
#define MIN_DEGREES 0

/** CLASS INSTANCE CREATION **/
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL); // Creation of Thinger
Servo servo[5]; // Creation of an array of 8 servos

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

  // Email = 5
  // Insta = 4
  // Facebook = 3
  // Messenger = 2
  // Whatsapp = 1

  thing.add_wifi(SSID, SSID_PASSWORD); // Connect the board to WiFi
  servo[0].attach(4); // Attach the first servo to pin 4
  servo[1].attach(5); // Attach the first servo to pin 4
  servo[2].attach(2); // Attach the first servo to pin 4
  servo[3].attach(16); // Attach the first servo to pin 4
  servo[4].attach(15); // Attach the first servo to pin 4

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

    Serial.print("WhatsApp Notifications - "); // Print WhatsApp Notifications
    Serial.println(whatsApp);
    servo[0].write(90 - (whatsApp * 5));
    //handleServos(0, whatsApp, 5);
    //servo[0].write(90 - (whatsApp * 5));

    Serial.print("Messenger Notifications - "); // Print Facebook Messenger notifications
    Serial.println(fbMessenger);
    //  handleServos(1, fbMessenger, 5);
    servo[1].write(90 - (fbMessenger * 5));
    //servo[1].write(90 - (fbMessenger * 5));

    Serial.print("Facebook Notifications - "); // Print Facebook notifications
    Serial.println(facebook);
    servo[2].write(90 - (facebook * 5));
    //  handleServos(2, facebook, 5);
    //servo[3].write(90 - (facebook * 5));

    Serial.print("Instagram Notifications - "); // Print Instagram Messenger notifications
    Serial.println(insta);
    //   handleServos(3, insta, 5);
    servo[3].write(90 - (insta * 5));
    //servo[2].write(90 - (insta * 5));

    Serial.print("Email Notifications - "); // Print Email notifications
    Serial.println(email);
    // handleServos(4, email, 5);
    servo[4].write(90 - (email * 5));
    //servo[4].write(90 - (email * 5));
  };
}

void handleServos(int servoNum, int notificationNum, int mult) {
  if ((servo[servoNum].read() < MAX_DEGREES) && (servo[servoNum].read() > MIN_DEGREES))
    servo[servoNum].write(90 - (notificationNum * mult)); // Move servo a multiplication of degrees // else if (servo[servoNum].read() >= MAX_DEGREES) {
  Serial.println("Handled");
}

void loop() {
  thing.handle();
  delay(1);
}
