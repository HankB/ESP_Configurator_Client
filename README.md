# ESP Configurator client

See <https://github.com/HankB/ESP_Configurator> for an overview and <https://github.com/HankB/ESP_Configurator_Server> for the corresponding server. The protocol is described in the server README.

The client broadcasts a request for configuration including the MAC address for identification and then waits for configuration messages from the server.

## 2025-03-20 Toolchain

PlatformIO (PIO) in VS Code on Debian Linux and using the Arduino library.

## Status

* 2025-03-20 Code started (compiles) but not loaded on the ESP. And now does not compile. :-/


## 2025-03-20 examples

* <https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/examples/WiFiUDPClient/WiFiUDPClient.ino>
* <https://github.com/espressif/arduino-esp32/blob/master/libraries/AsyncUDP/examples/AsyncUDPClient/AsyncUDPClient.ino>

Perhaps the AsyncUDP lib is the way to go.
