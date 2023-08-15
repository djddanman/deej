#include "pio_encoder.h"
#include "Adafruit_TinyUSB.h"

const int NUM_SLIDERS = 5; // Change to 5 if uncommenting last encoder in array

PioEncoder encoders[NUM_SLIDERS] = {
    PioEncoder(0, pio0),
    PioEncoder(2, pio0),
    PioEncoder(4, pio0),
    PioEncoder(6, pio0),
    PioEncoder(8, pio1) // Works every time if this line is commented
};

int EncoderValues[NUM_SLIDERS];

void setup() { 
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  for (int i = 0; i < NUM_SLIDERS; i++) {
    encoders[i].begin();
    EncoderValues[i] = 0;
    for (int j = 0; j <= i; j++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
    delay(500);
  }
  
  Serial.begin(9600);
  while(!Serial);
  Serial.write("Finishing init\n");
}

void loop() {
  updateSliderValues();
  sendSliderValues(); // Actually send data (all the time)
  // printSliderValues(); // For debug, comment out for normal use
  delay(10);
}

void updateSliderValues() {
  for (int i = 0; i < NUM_SLIDERS; i++) {
    int count = encoders[i].getCount();
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
