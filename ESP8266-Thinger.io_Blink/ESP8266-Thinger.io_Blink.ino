#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "frzruk"
#define DEVICE_ID "esp8266_huzzah"
#define DEVICE_CREDENTIAL "5tFfA#zZbN$%"

#define SSID "FY"
#define SSID_PASSWORD "wifi1212"
#define pin 0

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);
  Serial.println("connected?");
  
  thing["led"] << [](pson & in) {
    if (in.is_empty()) {
      in = (bool) digitalRead(pin);
    }
    else {
      digitalWrite(pin, in ? HIGH : LOW);
    };
  };

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}
