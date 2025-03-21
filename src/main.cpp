#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <esp_wifi.h>

AsyncUDP udp;

static const size_t bcast_buff_len = 30;
static char bcast_buff[bcast_buff_len];

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin();
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("no wifi yet");
    delay(1000);
  }
  Serial.println("yes wifi yet");
  if (udp.connect(IPAddress(255, 255, 255, 255), 5016))
  {
    Serial.println("UDP connected");
    udp.onPacket([](AsyncUDPPacket packet)
                 {
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
      packet.printf("Got %u bytes of data", packet.length()); });
    // Send unicast
    uint8_t baseMac[6];
    esp_err_t ret = esp_wifi_get_mac(WIFI_IF_STA, baseMac);
    if (ret == ESP_OK)
    {
      Serial.printf("%02x:%02x:%02x:%02x:%02x:%02x\n",
                    baseMac[0], baseMac[1], baseMac[2],
                    baseMac[3], baseMac[4], baseMac[5]);
      snprintf(bcast_buff, bcast_buff_len,
               "request-config|%02x%02x%02x%02x%02x%02x",
               baseMac[0], baseMac[1], baseMac[2],
               baseMac[3], baseMac[4], baseMac[5]);
      udp.print(bcast_buff);
    }
    else
    {
      Serial.println("Failed to read MAC address");
    }
  }
}

void loop()
{
  Serial.println("looping");
  udp.broadcastTo(bcast_buff, 5016);
  // udp.print(bcast_buff); also works.
  delay(1000);
}
