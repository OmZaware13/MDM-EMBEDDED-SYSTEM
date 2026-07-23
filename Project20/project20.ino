#include <ArduinoBLE.h>

BLEService ledService("180A");

BLEByteCharacteristic ledCharacteristic(
  "2A57",
  BLEWrite
);

void setup() {
  Serial.begin(9600);

  pinMode(LEDR, OUTPUT);

  // Red LED initially OFF
  // Nano RGB LED is active-LOW
  digitalWrite(LEDR, HIGH);

  if (!BLE.begin()) {
    Serial.println("BLE failed!");
    while (1);
  }

  BLE.setLocalName("NanoRGB");

  BLE.setAdvertisedService(ledService);

  ledService.addCharacteristic(ledCharacteristic);

  BLE.addService(ledService);

  BLE.advertise();

  Serial.println("NanoRGB is ready");
}

void loop() {

  BLEDevice central = BLE.central();

  if (central) {

    Serial.println("Phone connected");

    while (central.connected()) {

      if (ledCharacteristic.written()) {

        char command = ledCharacteristic.value();

        if (command == 'A') {
          digitalWrite(LEDR, LOW);
          Serial.println("RED LED ON");
        }

        else if (command == 'B') {
          digitalWrite(LEDR, HIGH);
          Serial.println("RED LED OFF");
        }
      }
    }

    Serial.println("Phone disconnected");
  }
}
