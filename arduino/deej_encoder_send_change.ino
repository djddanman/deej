#include "pio_encoder.h"
#include "Adafruit_TinyUSB.h"

//PioEncoder knobMaster(0);

//void setup() {
//  encoder.begin();
//  Serial.begin(115200);
//  while(!Serial);

//}

//void loop() {
//  Serial.println(encoder.getCount());
//  delay(10);
//}

const int NUM_SLIDERS = 3;
//const int analogInputs[NUM_SLIDERS] = {A0, A1, A2, A3, A4};
PioEncoder encoders[NUM_SLIDERS] = {0, 2, 4};
//PioEncoder knobMaster(0);
//PioEncoder knobChrome(2);
//PioEncoder knobDiscord(4);

int EncoderValues[NUM_SLIDERS];

void setup() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    encoders[i].begin();
    EncoderValues[i] = 0;
  }
  //EncoderValues[0] = 50;

  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug
  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    int count = encoders[i].getCount();
      //if (EncoderValues[i] + count <= 100 && EncoderValues[i] + count >= 0) {
      //  EncoderValues[i] += count;
      //}
      EncoderValues[i] = count;
    encoders[i].reset();
  }
}

void sendSliderValues() {
  String builtString = String("");

  for (int i = 0; i < NUM_SLIDERS; i++) {
    int value = EncoderValues[i];
    builtString += String((int)value);

    if (i < NUM_SLIDERS - 1) {
      builtString += String("|");
    }
  }
  
  Serial.println(builtString);
}

void printSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    String printedString = String("Slider #") + String(i + 1) + String(": ") + String(EncoderValues[i]) + String(" mV");
    Serial.write(printedString.c_str());

    if (i < NUM_SLIDERS - 1) {
      Serial.write(" | ");
    } else {
      Serial.write("\n");
    }
  }
}
