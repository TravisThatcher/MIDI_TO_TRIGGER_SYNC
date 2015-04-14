#include "MIDI.h"

// Roland CR-5000 Midi Sync and Midi Control
// Rev 03. 04-14 Travis Thatcher - recompas@gmail.com
// This version is used for interfacing with Rolands CR-5000 which uses
// negative going triggers. For regular V+ trigger circuits reverse all 
// HIGH / LOW logic in the code.
// Note pins A0 and A1 are also set to digital output mode in order to pass on DIN SYNC to another device


// midi values
#define OFF 1
#define ON 2
#define WAIT 3

#define NUMTRIGS 10
#define START_STOP 13 // Digital logic pin for start/stop signal
#define CLOCK_PIN 2 // Clock out pin for CR

#define CLOCK_LENGTH 3000 // Play with this value if you are getting strange clock jitter, time in Micro-seconds

#define TRIGGER_TIME 20

boolean DEBUG = false;  // to turn off all debug print messages

// Set these to whatever works for your circuit connections
int triggerPins[] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; // trigger pins
int triggerTimes[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // hold times for triggers

// Initialize all triggers to off
int triggerStates[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};


int currentTime=0;
int clockTime=0;

byte incomingByte;
byte velocity;

void setup() {
  MIDI.turnThruOff();
  if(!DEBUG){
  MIDI.begin(1);  // Set midi channel here
  }else{
    Serial.begin(19200); // Othewise debug mode = no midi, allows for printing debug info to serial monitor
  }
  if(DEBUG){
    Serial.println("hello!");
  }  

  // setup output pins
  pinMode(START_STOP, OUTPUT);
  digitalWrite(START_STOP, HIGH);
  
  pinMode(CLOCK_PIN, OUTPUT);
  digitalWrite(CLOCK_PIN, LOW);
  
  // analog pins
  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  
  MIDI.setHandleStart(HandleStart);
  MIDI.setHandleStop(HandleStop);
  MIDI.setHandleContinue(HandleContinue);
  MIDI.setHandleClock(HandleClock);
  MIDI.setHandleNoteOn(HandleNoteOn);
}

void loop() {
  
   MIDI.read();
   
  
  currentTime = millis(); 
    
  
  // check out the trigger states
  for(int i=0; i<NUMTRIGS; i++){
    if(triggerStates[i]==LOW){
      if(currentTime - triggerTimes[i] > TRIGGER_TIME){
        if(DEBUG){
          Serial.println("turning off!");
        }
        digitalWrite(triggerPins[i], HIGH);
        triggerStates[i]=HIGH; 
      }
    }
  }
  
}

void HandleStart() {
  digitalWrite(START_STOP, LOW);
  digitalWrite(A1, HIGH);
}

void HandleContinue() {
  digitalWrite(START_STOP, LOW);
  digitalWrite(A1, HIGH);
}

void HandleStop() {
  digitalWrite(START_STOP, HIGH);
  digitalWrite(A1, LOW);
}

void HandleClock() { 
  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(A0, HIGH);
  delayMicroseconds(CLOCK_LENGTH);
  digitalWrite(CLOCK_PIN, HIGH);  
  digitalWrite(A0, LOW);  
}

void HandleNoteOn(byte channel, byte pitch, byte velocity){
  if(DEBUG){
    Serial.println(pitch);
  }
  // triggers!
  for(int i=0; i<NUMTRIGS; i++){
    
    if(pitch-60==i){
      digitalWrite(triggerPins[i], LOW);
      triggerStates[i] = LOW;
      triggerTimes[i] = currentTime;
    }else{
      
    }
  }
  
}
