#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>

AsyncUDP udp;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  while(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("no wifi yet");
    delay(1000);
  }
  Serial.println("yes wifi yet");
  if (udp.connect(IPAddress(255, 255, 255, 255), 5016)) {
    Serial.println("UDP connected");
    udp.onPacket([](AsyncUDPPacket packet) {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      //reply to the client
      packet.printf("Got %u bytes of data", packet.length());
    });
    //Send unicast
    udp.print("Hello Server!");
  }
}

void loop() {
  Serial.println("looping");
  udp.broadcastTo("Anyone here?", 5016);
  delay(1000);
}
