#include <Encoder.h>
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// Define the pin connections for each encoder.
Encoder jogWheel1(2, 3);  // Connect Encoder 1 pins to 2, 3
Encoder jogWheel2(4, 5);  // Connect Encoder 2 pins to 4, 5
Encoder trackSelector(6, 7);  // Connect track selector encoder pins to 6, 7

// Define the pin connections for each button.
int playButtonDeck1 = 8; // Connect Play button of Deck1 to pin 8
int playButtonDeck2 = 9; // Connect Play button of Deck2 to pin 9
int cueButtonDeck1 = 10; // Connect Cue button of Deck1 to pin 10
int cueButtonDeck2 = 11; // Connect Cue button of Deck2 to pin 11
int headphoneButton1 = 12; // Connect headphone button for Deck1 to pin 12
int headphoneButton2 = 13; // Connect headphone button for Deck2 to pin 13
int loadButtonDeck1 = 14; // Connect Load Track button for Deck1 to pin 14
int loadButtonDeck2 = 15; // Connect Load Track button for Deck2 to pin 15

// variables to keep the last encoder values
long oldPositionJog1  = -999;
long oldPositionJog2  = -999;
long oldPositionTrack = -999;

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Define the mode for each button pin.
  pinMode(playButtonDeck1, INPUT_PULLUP);
  pinMode(playButtonDeck2, INPUT_PULLUP);
  pinMode(cueButtonDeck1, INPUT_PULLUP);
  pinMode(cueButtonDeck2, INPUT_PULLUP);
  pinMode(headphoneButton1, INPUT_PULLUP);
  pinMode(headphoneButton2, INPUT_PULLUP);
  pinMode(loadButtonDeck1, INPUT_PULLUP);
  pinMode(loadButtonDeck2, INPUT_PULLUP);
}

void loop() {
  int val;

  // Read the slide potentiometers
  for(int i = A0; i <= A2; i++){
    val = analogRead(i);
    val = map(val, 0, 1023, 0, 127);
    MIDI.sendControlChange(i, val, 1);
    delay(10);
  }

  // Read the rotary potentiometers
  for(int i = A3; i <= A12; i++){
    val = analogRead(i);
    val = map(val, 0, 1023, 0, 127);
    MIDI.sendControlChange(i, val, 1);
    delay(10);
  }

  long newPositionJog1 = jogWheel1.read();
  if (newPositionJog1 != oldPositionJog1) {
    oldPositionJog1 = newPositionJog1;
    MIDI.sendControlChange(10, constrain(oldPositionJog1, 0, 127), 1);
  }

  long newPositionJog2 = jogWheel2.read();
  if (newPositionJog2 != oldPositionJog2) {
    oldPositionJog2 = newPositionJog2;
    MIDI.sendControlChange(11, constrain(oldPositionJog2, 0, 127), 1);
  }

  long newPositionTrack = trackSelector.read();
  if (newPositionTrack != oldPositionTrack) {
    oldPositionTrack = newPositionTrack;
    MIDI.sendControlChange(12, constrain(oldPositionTrack, 0, 127), 1);
  }

  // Read the button states and send a MIDI message when pressed.
  if (digitalRead(playButtonDeck1) == LOW) {
    MIDI.sendNoteOn(60, 127, 1);  // 60 = C4 in MIDI, adjust to your needs
  }
  if (digitalRead(playButtonDeck2) == LOW) {
    MIDI.sendNoteOn(61, 127, 1);  // adjust to your needs
  }
  if (digitalRead(cueButtonDeck1) == LOW) {
    MIDI.sendNoteOn(62, 127, 1);  // adjust to your needs
  }
  if (digitalRead(cueButtonDeck2) == LOW) {
    MIDI.sendNoteOn(63, 127, 1);  // adjust to your needs
  }
  if (digitalRead(headphoneButton1) == LOW) {
    MIDI.sendNoteOn(64, 127, 1);  // adjust to your needs
  }
  if (digitalRead(headphoneButton2) == LOW) {
    MIDI.sendNoteOn(65, 127, 1);  // adjust to your needs
  }
  if (digitalRead(loadButtonDeck1) == LOW) {
    MIDI.sendNoteOn(66, 127, 1);  // adjust to your needs
  }
  if (digitalRead(loadButtonDeck2) == LOW) {
    MIDI.sendNoteOn(67, 127, 1);  // adjust to your needs
  }

  delay(10);  // Add a small delay to avoid bouncing issues
}
