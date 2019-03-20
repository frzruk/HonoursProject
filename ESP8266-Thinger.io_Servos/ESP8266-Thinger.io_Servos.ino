#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include <Servo.h>

#define USERNAME "frzruk"
#define DEVICE_ID "esp8266_huzzah"
#define DEVICE_CREDENTIAL "5tFfA#zZbN$%"

#define SSID "StudentResidences"
#define SSID_PASSWORD ""
#define pin 0

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
Servo myServoInstance;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);
  Serial.println("connected?");

  thing["servo"] << [](pson & in) {
    if (in.is_empty()) {
      in = (bool) digitalRead(pin);
    }
    else {
      digitalWrite(pin, in ? HIGH : LOW);
    }
  };
}

void loop() {
  thing.handle();
}
