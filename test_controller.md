# Test DIY controller
Use potentiometer to control volume on Deck 1 on Mixxx.
Mixxx installed on Raspberry Pi.
Hardware controlled with Arduino.

1. Place potentiometer (pot) on the breadboard, do wiring.

2. Program Arduino
```
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  int sensorValue = analogRead(analogInPin);
  // map it to the range of MIDI values:
  int outputValue = map(sensorValue, 0, 1023, 0, 127);
  // send the output value:
  Serial.println(outputValue);
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
```