#include <PDM.h>

short sampleBuffer[256];
volatile int samplesRead = 0;

void onPDMdata() {
  // Get number of available bytes
  int bytesAvailable = PDM.available();

  // Read microphone data
  PDM.read(sampleBuffer, bytesAvailable);

  samplesRead = bytesAvailable / 2;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Set callback function
  PDM.onReceive(onPDMdata);

  // Start microphone:
  // 1 channel (mono), 16000 Hz sample rate
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start microphone!");
    while (1);
  }

  Serial.println("Sound Level Logging Started");
}

void loop() {

  if (samplesRead > 0) {

    int maxAmplitude = 0;

    // Find peak amplitude
    for (int i = 0; i < samplesRead; i++) {
      int amplitude = abs(sampleBuffer[i]);

      if (amplitude > maxAmplitude) {
        maxAmplitude = amplitude;
      }
    }

    // Print sound level
    Serial.print("Sound Level: ");
    Serial.println(maxAmplitude);

    samplesRead = 0;

    delay(100);
  }
}