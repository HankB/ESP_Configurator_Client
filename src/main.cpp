#include <Arduino.h>
#include <WiFi.h>
//#include <WiFiUdp.h>
#include <AsyncUDP.h>

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  while(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("no wifi yet");
    delay(1000);
  }
}

void loop() {

  udp.begin();
  UDP.broadcast()
  delay(1000);
}
