// this code reads 1 potentiometer and 1 encoder connected to Arduino and sends MIDI messages.

#include <MIDI.h>
#include <Encoder.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

Encoder myEnc(2, 3);  // Create an instance of the encoder (CLK pin, DT pin)

int lastPotValue = -1;  // Last potentiometer value, to detect changes
long oldPosition  = -999;  // Last encoder value, to detect changes

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen on all MIDI channels
}

void loop() {
  // read the analog in value:
  int sensorValue = analogRead(analogInPin);
  // map it to the range of MIDI values:
  int outputValue = map(sensorValue, 0, 1023, 0, 127);
  
  // Only send MIDI message if potentiometer value changed
  if (outputValue != lastPotValue) {
    MIDI.sendControlChange(1, outputValue, 1);  // Control number 1, value, channel 1
    lastPotValue = outputValue;
  }

  // read the encoder value:
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    // Convert the encoder value to a 7-bit MIDI CC value (0-127)
    // Assuming you have a 24ppr encoder, and you want one full rotation to span the full MIDI range
    int ccValue = map(newPosition % 24, 0, 23, 0, 127);
    // Send the MIDI CC message on channel 1, controller number 2 (arbitrary choice)
    MIDI.sendControlChange(2, ccValue, 1);
  }
  delay(2);
}
