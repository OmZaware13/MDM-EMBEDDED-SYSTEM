#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);

  while (!Serial);

  // Initialize APDS9960 sensor
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
    while (1);
  }

  Serial.println("Gesture Detection Started");
}

void loop() {

  // Check if a gesture is available
  if (APDS.gestureAvailable()) {

    // Read the gesture
    int gesture = APDS.readGesture();

    switch (gesture) {

      case GESTURE_UP:
        Serial.println("UP");
        break;

      case GESTURE_DOWN:
        Serial.println("DOWN");
        break;

      case GESTURE_LEFT:
        Serial.println("LEFT");
        break;

      case GESTURE_RIGHT:
        Serial.println("RIGHT");
        break;

      default:
        break;
    }
  }
}