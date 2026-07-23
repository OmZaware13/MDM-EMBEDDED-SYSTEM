#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);

  // Set RGB LED pins as output
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Turn all LEDs OFF
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);

  // Initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.println("IMU Tilt RGB LED Control");
}

void loop() {
  float x, y, z;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);

    // Turn all LEDs OFF first
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);

    if (x < -0.3) {
      // Left Tilt -> RED
      Serial.println("Left - RED");
      digitalWrite(LEDR, LOW);
    }
    else if (x > 0.3) {
      // Right Tilt -> GREEN
      Serial.println("Right - GREEN");
      digitalWrite(LEDG, LOW);
    }
    else if (y > 0.3) {
      // Front Tilt -> BLUE
      Serial.println("Front - BLUE");
      digitalWrite(LEDB, LOW);
    }
    else if (y < -0.3) {
      // Back Tilt -> ORANGE
      Serial.println("Back - ORANGE");
      digitalWrite(LEDR, LOW);
      digitalWrite(LEDG, LOW);
    }

    delay(200);
  }
}