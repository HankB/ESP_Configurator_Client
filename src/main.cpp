#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>

// put function declarations here:
int myFunction(int, int);

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
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}