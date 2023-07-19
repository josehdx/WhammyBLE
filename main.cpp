#include <Arduino.h>

#include <Control_Surface.h>

#include <AH/Hardware/MultiPurposeButton.hpp>

BluetoothMIDI_Interface midi;

// Instantiate a PBPotentiometer object
PBPotentiometer potentiometer {
  15,        // Analog pin connected to potentiometer
  CHANNEL_1, // MIDI Channel 1
};


// Mapping Pitchbend
constexpr analog_t minimumValue = 0;
constexpr analog_t maximumValue = 16383; 
constexpr analog_t margin = 300;

analog_t mappingFunction(analog_t raw) {
  raw = constrain(raw, minimumValue, maximumValue);
  if (raw <= 8192 - margin)
    return map(raw, minimumValue, 8192 - margin, 0, 8192 + 64); 
  else if (raw >= 8192 + margin)
    return map(raw, 8192 + margin, maximumValue, 8192 + 64, 16383);
  else
    return 8192 + 64;
}



void setup() {

  Control_Surface.begin();
  potentiometer.map(mappingFunction); // Add the mapping function to the potentiometer

}

void loop() {

  
  Control_Surface.loop();
     delay(1);
}