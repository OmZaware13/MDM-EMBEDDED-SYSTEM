#include <Arduino.h>
#include "mbed.h"

// Create two RTOS threads
rtos::Thread ledThread;
rtos::Thread serialThread;

// Task 1: Blink LED
void blinkLED() {
    while (true) {
        digitalWrite(LED_BUILTIN, LOW);
        rtos::ThisThread::sleep_for(500);

        digitalWrite(LED_BUILTIN, HIGH);
        rtos::ThisThread::sleep_for(500);
    }
}

// Task 2: Print message
void printMessage() {
    while (true) {
        Serial.println("RTOS Task 2 is running");
        rtos::ThisThread::sleep_for(1000);
    }
}

void setup() {
    Serial.begin(9600);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    // Start both RTOS threads
    ledThread.start(blinkLED);
    serialThread.start(printMessage);
}

void loop() {
    // RTOS threads run independently
}