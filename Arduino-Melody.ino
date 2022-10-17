/*
  Based on Tom Igoe's code
  http://www.arduino.cc/en/Tutorial/Tone
*/

#include "pitches.h"


const int buzzerPin = 3;
const int buttonPin = 7;
int buttonState = 7;
const int ledPin = 9;

// notes in the melody:
// use 0 for a rest
// put each measure on its own line
int tetrisMelody[] = {
  NOTE_E4, NOTE_B4, NOTE_C4, NOTE_D4, 0, 
  NOTE_C4, NOTE_B4, NOTE_A4, 0,
  NOTE_A4, NOTE_C4, NOTE_E4, 0,
  NOTE_D4, NOTE_C4, NOTE_B4, 0,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A4, NOTE_A4, 0, 0,
  NOTE_D4, NOTE_F4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, 0,
  NOTE_C4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4, 0,
  NOTE_B4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A4, NOTE_A4
  
};
int brazilMelody[] = {
  NOTE_C4, NOTE_E4, NOTE_G4,
  NOTE_B4, 0, 0, NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_B4, 0, NOTE_C4, NOTE_E4, NOTE_G4, 0,
  NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4,
  NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4, 0,
  NOTE_G4, NOTE_E4, 0, NOTE_E4, NOTE_D4, NOTE_F4, NOTE_C4,
  NOTE_C4, 0, 0, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_D4,
  NOTE_F4, NOTE_A4, NOTE_C4, 0, NOTE_B4, NOTE_B4, NOTE_G4,
  NOTE_B4, NOTE_B4, NOTE_G4, 0,
  NOTE_B4, NOTE_G4, NOTE_B4, NOTE_G4
};
int sonicMelody[] = {
  NOTE_C6, NOTE_C6, NOTE_A5, NOTE_C6, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_G5,
  NOTE_A5, NOTE_E6, NOTE_D6, NOTE_C6, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_G5,
  NOTE_C6, NOTE_A5, NOTE_C6, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_G5,
  NOTE_A5, NOTE_A5, NOTE_F5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_G5,
  NOTE_C5, NOTE_C5, NOTE_E5, NOTE_D5,
  NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_C5, NOTE_C5, NOTE_E5
};
// note durations: 1 = whole note, 4 = quarter note, 8 = eighth note, etc.:
// be sure each note or rest in the melody above has a corresponding duration below
// put each measure on its own line
int tetrisDurations[] = {
  2, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
  4, 2, 2, 4, 4, 2, 2,
  4, 4, 2, 4, 4, 4, 4,
  4, 2, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2, 2
};

int brazilDurations[] = {
  4, 4, 4,
  4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 
  4, 4, 4, 4, 4,
  4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4, 4,
};

int sonicDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4,
  4, 4, 4,
  4, 4, 4,
  4, 4, 4,
};

// set the tempo
// a tempo of 60 is one beat per second
// a tempo of 120 would be twice as fast
int beatsPerMinute = 298;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH){

    digitalWrite(ledPin, HIGH);
    playSonic();
    delay(3000);
    playBrazil();
    delay(3000);
    playTetris();
    delay(3000);
    digitalWrite(ledPin, LOW);

  }
  else{
    digitalWrite (ledPin, LOW);
  }
}


void playBrazil(){
// iterate over the notes of the melody:
  int len = sizeof(brazilMelody)/sizeof(brazilMelody[0]);
  for (int thisNote = 0; thisNote < len; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = static_cast<int>(1000 / brazilDurations[thisNote] * 298 / beatsPerMinute);
    tone(buzzerPin, brazilMelody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
    
  }
 }

 void playTetris(){
// iterate over the notes of the melody:
  int len = sizeof(tetrisMelody)/sizeof(tetrisMelody[0]);
  for (int thisNote = 0; thisNote < len; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = static_cast<int>(1000 / tetrisDurations[thisNote] * 298 / beatsPerMinute);
    tone(buzzerPin, tetrisMelody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
    
  }
 }

 void playSonic(){
// iterate over the notes of the melody:
  int len = sizeof(sonicMelody)/sizeof(sonicMelody[0]);
  for (int thisNote = 0; thisNote < len; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = static_cast<int>(1000 / sonicDurations[thisNote] * 298 / beatsPerMinute);
    tone(buzzerPin, sonicMelody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzerPin);
    
  }
 }
