#include "stille-nacht.h"

/* 
  Silent Night
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/

/*
  Player adjusted to remove blocking delays.
    - start(): Will trigger the melody
    - async_play(): Call once every loop

*/

// change this to make the song slower or faster
int tempo = 120;

// change this to whichever pin you want to use
uint8_t buzzer;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

    // Silent Night, Original Version
    // Score available at https://musescore.com/marcsabatella/scores/3123436

    NOTE_G4,
    -4,
    NOTE_A4,
    8,
    NOTE_G4,
    4,
    NOTE_E4,
    -2,
    NOTE_G4,
    -4,
    NOTE_A4,
    8,
    NOTE_G4,
    4,
    NOTE_E4,
    -2,
    NOTE_D5,
    2,
    NOTE_D5,
    4,
    NOTE_B4,
    -2,
    NOTE_C5,
    2,
    NOTE_C5,
    4,
    NOTE_G4,
    -2,

    NOTE_A4,
    2,
    NOTE_A4,
    4,
    NOTE_C5,
    -4,
    NOTE_B4,
    8,
    NOTE_A4,
    4,
    NOTE_G4,
    -4,
    NOTE_A4,
    8,
    NOTE_G4,
    4,
    NOTE_E4,
    -2,
    NOTE_A4,
    2,
    NOTE_A4,
    4,
    NOTE_C5,
    -4,
    NOTE_B4,
    8,
    NOTE_A4,
    4,
    NOTE_G4,
    -4,
    NOTE_A4,
    8,
    NOTE_G4,
    4,
    NOTE_E4,
    -2,

    NOTE_D5,
    2,
    NOTE_D5,
    4,
    NOTE_F5,
    -4,
    NOTE_D5,
    8,
    NOTE_B4,
    4,
    NOTE_C5,
    -2,
    NOTE_E5,
    -2,
    NOTE_C5,
    4,
    NOTE_G4,
    4,
    NOTE_E4,
    4,
    NOTE_G4,
    -4,
    NOTE_F4,
    8,
    NOTE_D4,
    4,
    NOTE_C4,
    -2,
    NOTE_C4,
    -1,
};

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
boolean silent = true, play = false;
long nextChange = 0;
int activeNote = 0;
long time = 0;

void start(uint8_t pin)
{
    activeNote = 0;
    play = true;
    buzzer = pin;
}

boolean async_play()
{
    time = millis();
    if (!play || time < nextChange)
    {
        return play;
    }

    if (silent)
    {
        divider = melody[(activeNote) + 1];
        noteDuration = (divider > 0) 
            ? (wholenote) / divider
            // dotted notes are represented with negative durations!!
            : ((wholenote) / abs(divider)) * 1.5;
        
        Serial.println("Play note: " + String(activeNote, DEC) + "(" + melody[activeNote * 2] + ")" + " for " + String(noteDuration, DEC) + " milliseconds");
        tone(buzzer, melody[activeNote]);
        // play tone slightly shorter
        noteDuration *= 0.9;
        activeNote += 2;
    }
    else
    {
        noteDuration = 5;
        Serial.println("Silence for " + String(noteDuration, DEC) + " milliseconds...");
        noTone(buzzer);
        if (activeNote >= notes * 2)
        {
            play = false;
        }
    }

    silent = !silent;
    nextChange = time + noteDuration;
    return play;
}