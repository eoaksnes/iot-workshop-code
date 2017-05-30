/*  Example of playing a sampled sound,
    using Mozzi sonification library.
  
    Demonstrates one-shot samples scheduled
    with EventDelay.
  
    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or 
    check the README or http://sensorium.github.com/Mozzi/
  
    Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users
  
    Tim Barrass 2012, CC by-nc-sa.
*/

#include <MozziGuts.h>
#include <Sample.h> // Sample template
#include "drumsamples/clap_sample.h"
#include "drumsamples/hihat_sample.h"
#include "drumsamples/kick_sample.h"
#include "drumsamples/snare_sample.h"
#include <EventDelay.h>

#define CONTROL_RATE 64

// use: Sample <table_size, update_rate> SampleName (wavetable)
Sample <CLAP_NUM_CELLS, AUDIO_RATE> clapSample(CLAP_DATA);
Sample <HIHAT_NUM_CELLS, AUDIO_RATE> hihatSample(HIHAT_DATA);
Sample <KICK_NUM_CELLS, AUDIO_RATE> kickSample(KICK_DATA);
Sample <SNARE_NUM_CELLS, AUDIO_RATE> snareSample(SNARE_DATA);


#define CLAP_PIN 2
#define HIHAT_PIN 4
#define KICK_PIN 7
#define SNARE_PIN 8

EventDelay clapDebounceDelay;
EventDelay hihatDebounceDelay; 
EventDelay kickDebounceDelay;
EventDelay snareDebounceDelay;

#define DEBOUNCE_DELAY_MILLIS 5

int clapButtonState = HIGH;
int hihatButtonState = HIGH;
int kickButtonState = HIGH;
int snareButtonState = HIGH;

void setup(){
    Serial.begin(115200);

    pinMode(CLAP_PIN, INPUT_PULLUP);
    pinMode(HIHAT_PIN, INPUT_PULLUP);
    pinMode(KICK_PIN, INPUT_PULLUP);
    pinMode(SNARE_PIN, INPUT_PULLUP);

    clapSample.setFreq((float)CLAP_SAMPLERATE / (float)CLAP_NUM_CELLS);
    hihatSample.setFreq((float)HIHAT_SAMPLERATE / (float)HIHAT_NUM_CELLS);
    kickSample.setFreq((float)KICK_SAMPLERATE / (float)KICK_NUM_CELLS);
    snareSample.setFreq((float)SNARE_SAMPLERATE / (float)SNARE_NUM_CELLS);

    clapDebounceDelay.set(DEBOUNCE_DELAY_MILLIS);
    hihatDebounceDelay.set(DEBOUNCE_DELAY_MILLIS);
    kickDebounceDelay.set(DEBOUNCE_DELAY_MILLIS);
    snareDebounceDelay.set(DEBOUNCE_DELAY_MILLIS);

    startMozzi(CONTROL_RATE);
}



boolean buttonPressed(EventDelay* debouceDelay, uint8_t buttonPin, int* buttonState){
    if (debouceDelay->ready()) {
        if (digitalRead(buttonPin) == LOW) {
            if (*buttonState == HIGH) {
                debouceDelay->start();
                *buttonState = LOW;
                return true;
            }
        }
        else {
            *buttonState = HIGH;
        }
    }

    return false;
}

void updateControl(){

    if (buttonPressed(&clapDebounceDelay, CLAP_PIN, &clapButtonState))
        clapSample.start();

    if (buttonPressed(&hihatDebounceDelay, HIHAT_PIN, &hihatButtonState))
        hihatSample.start();
    
    if (buttonPressed(&kickDebounceDelay, KICK_PIN, &kickButtonState))
        kickSample.start();

    if (buttonPressed(&snareDebounceDelay, SNARE_PIN, &snareButtonState))
        snareSample.start();

}

int updateAudio(){
  return (int) (clapSample.next() + hihatSample.next() + kickSample.next() + snareSample.next());
}


void loop(){
  audioHook();
}


