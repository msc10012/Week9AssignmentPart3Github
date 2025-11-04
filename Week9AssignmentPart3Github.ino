#include "BetterButton.h"

int button1Pin = 28;
int button2Pin = 29;
int button3Pin = 30;
int button4Pin = 31;
int midiNotes[4] = { 60, 62, 64, 65 };
int ledPins[4] = { 9, 10, 11, 12 };

BetterButton button1(button1Pin, 0);
BetterButton button2(button2Pin, 1);
BetterButton button3(button3Pin, 2);
BetterButton button4(button4Pin, 3);

BetterButton* buttonArray[4] = { &button1, &button2, &button3, &button4 };

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
  pinMode(ledPins[i], OUTPUT);
  }
  for (int i = 0; i < 4; i++) {
    buttonArray[i]->pressHandler(onPress);
    buttonArray[i]->releaseHandler(onRelease);
  }
}

void loop() {
  for(int i=0; i<4; i++) {
    buttonArray[i]->process();
  }
}

void onPress(int val) {
  Serial.print(val);
  Serial.println(" on");
  usbMIDI.sendNoteOn(midiNotes[val], 127, 1);
  digitalWrite(ledPins[0], HIGH);
}

void onRelease(int val) {
  Serial.print(val);
  Serial.println(" off");
  usbMIDI.sendNoteOff(midiNotes[val], 0, 1);
  digitalWrite(ledPins[0], LOW);
}
