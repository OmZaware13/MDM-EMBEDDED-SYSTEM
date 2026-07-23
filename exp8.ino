#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);

  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.println("IMU Tilt Direction Detection");
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    if (x > 0.3) {
      Serial.println("Right");
    }
    else if (x < -0.3) {
      Serial.println("Left");
    }
    else if (y > 0.3) {
      Serial.println("Front");
    }
    else if (y < -0.3) {
      Serial.println("Back");
    }
    else {
      Serial.println("Flat");
    }

    delay(300);
  }
}