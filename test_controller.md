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

# 3. On RPI get signal from Arduino, convert to MIDI
OPTION 1
We'll use FortySevenEffects' Arduino MIDI Library. Chat GPT first told me to use ttymidi, but in README I saw that it is soon to be deprecated and recommendation to go for 47Effects.
- Go to https://github.com/FortySevenEffects/arduino_midi_library
- Click the green "Code" button which is towards the top right.
- In the dropdown, click "Download ZIP".
- Save the ZIP file to your computer.
- Open the Arduino IDE.
- In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library...
- In the file dialog that opens, navigate to where you saved the downloaded ZIP file and select it.
- Click "Open". The Arduino IDE will then install the library for you. You can verify this by going to Sketch > Include Library. In the list of libraries, you should now see "MIDI Library".
- Restart Arduino.

OPTION 2
Using ttymidi on Linux
```
git clone https://github.com/cjbarnes18/ttymidi.git
cd ttymidi
make
sudo make install
```
Determine the serial port for the Arduino by typing ls /dev/tty* in the terminal. It should show up as something like /dev/ttyACM0 or /dev/ttyUSB0.

Start ttymidi, replace ACM0 with your port
```
ttymidi -s /dev/ttyACM0
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
