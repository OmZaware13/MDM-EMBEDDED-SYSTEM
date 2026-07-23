#include <Arduino.h>
#include <ArduinoBLE.h>
#include <Arduino_APDS9960.h>

// Create BLE Service
BLEService sensorService("180C");

// Create BLE Characteristic
BLEIntCharacteristic proximityCharacteristic(
  "2A56",
  BLERead | BLENotify
);

void setup() {
  Serial.begin(9600);

  // Initialize proximity sensor
  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS9960!");
    while (1);
  }

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE!");
    while (1);
  }

  // Set BLE device name
  BLE.setLocalName("Nano33BLE");

  // Set advertised service
  BLE.setAdvertisedService(sensorService);

  // Add characteristic to service
  sensorService.addCharacteristic(proximityCharacteristic);

  // Add service
  BLE.addService(sensorService);

  // Set initial value
  proximityCharacteristic.writeValue(0);

  // Start advertising
  BLE.advertise();

  Serial.println("BLE device is advertising...");
}

void loop() {

  // Wait for mobile phone to connect
  BLEDevice central = BLE.central();

  if (central) {

    Serial.print("Connected to: ");
    Serial.println(central.address());

    while (central.connected()) {

      // Check proximity data
      if (APDS.proximityAvailable()) {

        int proximity = APDS.readProximity();

        // Send value through BLE
        proximityCharacteristic.writeValue(proximity);

        Serial.print("Proximity: ");
        Serial.println(proximity);
      }

      delay(500);
    }

    Serial.println("Mobile disconnected");
  }
}