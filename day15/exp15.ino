#include <PDM.h>

short sampleBuffer[256];
volatile int samplesRead = 0;

const int threshold = 300;

void onPDMdata() {

  int bytesAvailable = PDM.available();

  PDM.read(sampleBuffer, bytesAvailable);

  samplesRead = bytesAvailable / 2;
}

void setup() {

  Serial.begin(9600);

  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);

  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);

  PDM.onReceive(onPDMdata);

  if (!PDM.begin(1, 16000)) {

    Serial.println("Microphone Error");

    while (1);
  }

  Serial.println("Sound Threshold Detection Started");
}

void loop() {

  if (samplesRead) {

    long sum = 0;

    for (int i = 0; i < samplesRead; i++) {

      sum += abs(sampleBuffer[i]);
    }

    int soundLevel = sum / samplesRead;

    Serial.print("Sound: ");
    Serial.println(soundLevel);

    if (soundLevel > threshold) {

      digitalWrite(LEDG, LOW);     // Green ON
      digitalWrite(LEDR, HIGH);

    } else {

      digitalWrite(LEDR, LOW);     // Red ON
      digitalWrite(LEDG, HIGH);
    }

    samplesRead = 0;
  }
}