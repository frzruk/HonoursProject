//https://api.thinger.io/v2/users/frzruk/devices/esp8266_huzzah/led?authorization=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJkZXYiOiJlc3A4MjY2X2h1enphaCIsImlhdCI6MTUzOTE3NTUyMSwianRpIjoiNWJiZGY0NjE5MjUxYWEwNGNjYzdlNWUyIiwicmVzIjpbImxlZCAiXSwidXNyIjoiZnJ6cnVrIn0.eSdGIzv3zxSodED9N5i-_eFTgoFxmrL6q7K2-uRdXHc
//This sketch gets the board to display the Username, Time and Text of a tweet created by myself (@frzrg)
//by hooking it into IFTTT and twitter commands as well as Thinger.io to handle the IoT part of it.

#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "frzruk"
#define DEVICE_ID "esp8266_huzzah"
#define DEVICE_CREDENTIAL "5tFfA#zZbN$%"

#define SSID "FY"
#define SSID_PASSWORD "wifi1212"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  Serial.begin(9600);
  thing.add_wifi(SSID, SSID_PASSWORD);
  Serial.println("connected?");
  
  thing["led"] << [](pson & in) {
    Serial.println("<NAME>");
    Serial.println((const char*) in["name"]);
    Serial.println("<TIME>");
    Serial.println((const char*) in["time"]);
    Serial.println("<TEXT>");
    Serial.println((const char*) in["text"]);
  };
}

void loop() {
  thing.handle();
}
