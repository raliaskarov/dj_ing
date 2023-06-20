** WORK IN PROGRSS **
# Test DIY controller
Use potentiometer to control volume on Deck 1 on Mixxx.
Mixxx installed on Raspberry Pi.
Hardware controlled with Arduino.

# 1. Place potentiometer (pot) on the breadboard, do wiring.

# 2. Program Arduino
```
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to

int lastValue = -1;  // Last potentiometer value, to detect changes

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen on all MIDI channels
}

void loop() {
  // read the analog in value:
  int sensorValue = analogRead(analogInPin);
  // map it to the range of MIDI values:
  int outputValue = map(sensorValue, 0, 1023, 0, 127);
  
  // Only send MIDI message if value changed
  if (outputValue != lastValue) {

    MIDI.sendControlChange(1, outputValue, 1);  // Control number 1, value, channel 1
    lastValue = outputValue;
  

  }
  delay(2);
}

```

# 3. Flash Arduino into MIDI class compliant device of required
Required of you use  ATmega16U2 chip for data transfer. That's if you own Arduino UNO or MEGA because their chips aren't recognized as audio device.
We'll use mocoLUFA https://github.com/kuwatay/mocolufa
Here's video guide https://www.youtube.com/watch?v=-bCz2I9SMAA&t=227s

I work on Raspberry PI.
Install firmware programmer 
```
sudo apt-get update
sudo apt-get install dfu-programmer
```
Get the firmware we need
```
wget https://morecatlab.akiba.coocan.jp/lab/morecat-lab/MocoLUFA.2014.03.19.zip
unzip MocoLUFA.2014.03.19.zip
```
See your device now recognized as Arduino
```
lsusb
```
Put device into DFU mode by looping 2 leftmost pins from top and bottom row of ICSP header of the 16U2 chip (having power of Arduino to the left).
Now your device will be recognized differently
```
lsusb
```
Rewrite firmware
```
sudo dfu-programmer atmega16u2 erase
sudo dfu-programmer atmega16u2 flash MocoLUFA.2014.03.19/ArduinoUNOR3/Arduino-usbserial-uno.hex
sudo dfu-programmer atmega16u2 reset
```
Replace "MocoLUFA.2014.03.19/ArduinoUNOR3/Arduino-usbserial-uno.hex" with the actual path to Arduino-usbserial-uno.hex file.
Reset device, unplug and plug to power.

Confirm it's now seen as USB audio
```
lsusb
```

NB: to bring device back into Aurduino mode (e.g. to write sketches into it):
Short (i.e. connect and disconnect) two leftmose pins of the bottom row of ICSP header of 16U2 chip (having power of Arduino to the left).
See result
```
lsusb
```



# 4. Configure Mixxx

1. Open Mixxx.
2. Go to "Options" -> "Preferences".
3. In the Preferences window, go to "Controllers".
4. Under the "Input Controller" section, you should see the ttymidi port. Enable it by checking the box.
5. With the ttymidi port selected, click on the "MIDI LEARN" button.
6. In the MIDI Learn screen, find the "VolumeDeck1" control.
7. Click on the "MIDI LEARN" button next to "VolumeDeck1", then turn the potentiometer on your physical controller. Mixxx should detect the MIDI message from the 8. Arduino and map it to the volume control.
9. Click "OK" to save your changes.
