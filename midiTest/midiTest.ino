#include <BLEMIDI_Transport.h>
#include <hardware/BLEMIDI_ESP32.h>

//BLEMIDI_CREATE_DEFAULT_INSTANCE()
 BLEMIDI_CREATE_INSTANCE("AWESOME_INSTRUMENT", MIDI)

int midiNote;

void setup() {
  MIDI.begin();
}

void loop() {
  midiNote = random(60, 80);
  MIDI.sendNoteOn(midiNote, 127, 1);
  delay(50);
  MIDI.sendNoteOff(midiNote, 0, 1);
  delay(1000);
}