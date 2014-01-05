/*
# Copyright 2014 Qu-Bit Electronix
# Author: Jason H. J. Lim (jason@jhjlim.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# See http://creativecommons.org/licenses/MIT/ for more information.
#
# -----------------------------------------------------------------------------
  _   _      _           _            
 | \ | |    | |         | |           
 |  \| | ___| |__  _   _| | __ _ ____ 
 | . ` |/ _ \ '_ \| | | | |/ _` V  _ \
 | |\  |  __/ |_) | |_| | | (_|    __/
 \_| \_/\___|_.__/ \__,_|_|\__,_|\___|
 -------------------------------------
 
 © 2013 Jason Lim && Andrew Ikenberry
 
 MIDI CC's to raspberry pi looping Mode
 ____________________________
 | Controls    | CC list:    |
 --------------|-------------|
 | Speed:      | 1   (MSB)   |
 |             | 2   (LSB)   |
 |-------------|-------------|
 | Pitch:      | 15  (MSB)   |
 |             | 16  (LSB)   |
 |-------------|-------------|
 | Loop Start: | 9   (MSB)   |
 |             | 10  (LSB)   |
 |-------------|-------------|
 | Loop End:   | 11  (MSB)   |
 |             | 12  (LSB)   |
 |-------------|-------------|
 | Glide:      | 70          |
 |-------------|-------------| 
 | Mix:        | 8           |
 |-------------|-------------|
 | Grain Size: | 4           |
 |-------------|-------------|
 | Grain Rate: | 5           |
 |-------------|-------------|
 | Recall:     | 92          |
 |-------------|-------------|
 | Freeze:     | 42          |
 |-------------|-------------|
 | Next:       | 24          |
 |-------------|-------------|
 | UtilityCC   | 23          |
 |=============|=============|
 
 */
#include <MIDI.h>

byte dontIgnore = 0;
byte firstOneShot = 0;
byte midiMute = 0;
byte switchBack = 0;
byte newMode = 0;
byte oneShot2LoopFlag = 0;
byte gpioStateChangePre = 0;
byte newFilesFlag = 0;
byte flashHold;
//external midi save/recall
byte midiRecall = 0;
byte exitEdit = 0;
//oneshot varispeed
int smp1MSB, smp2MSB, smp3MSB, smp4MSB, smp5MSB, smp6MSB, smp7MSB, smp8MSB;
int smp1LSB, smp2LSB, smp3LSB, smp4LSB, smp5LSB, smp6LSB, smp7LSB, smp8LSB;
//
int troubleShootMidi = 0;//0;//1 = on, 0 = off
//
int modeMidiNotes = 0;
int globalOperation = 0;//0 == Looping//1 == OneShot
int normalEdit = 0;//editMode state
int scatter, scatterRange = 1500;
int scatterToggle = 0;
int scatterState = 0;
int hideLights = 0;
int presetFlag = 1;
int utilityCC = 23;
int directionGate = 0;
//
int mappedMidiPitch, pitchMap, pitchMapPre = 0;
int mappedPitchMSB, mappedPitchLSB;
unsigned long bootUpMillis, bootUpMillisPre = 0;
//Forward lights no delay
unsigned long fader2Millis, fader2MillisPre = 0, fader2MillisPre1 = 0, fader2MillisPre2 = 0;
int lightBright, lightBrightmap;
int ledStep = 1;
int brightDir;
int randAlt1 = 10, randAlt2 = 10;
int ledChange1 = 255, ledChange2 = 1;
int alternateWhite = 1;
//New edit mode fade with no delays
int fadeOff = 1;
int t = 2500;
unsigned long faderMillis, faderMillisPre = 0;
int ledBrightness = 0, brightnessDir = 1, ledBrightConstrain;
int presetFlash = 0, presetToggleCCPass = 0;
int microsTimeThresh = 2000;
int rangeLight = 1;
int rangeControl = 1;
int redAltered, greenAltered, blueAltered;
int speedLEDlo, speedLEDhi;
int lastPreset;
//
int gpio, gpioRaw, gpioTog = 0, gpioStateChange = 0;
const int numStartReadings = 20;
int startReadings[numStartReadings];
int startIndex = 0;
int startTotal = 0;
int startAverage = 0;
int nextNext = 0;
int rollup = 0, initialVol = 0;
/////////////////////
// CV sensor timer
/////////////////////
int countVal = 200;
int countReturn = (countVal+50);
int countThresh = (countVal-1);
int presetSelect, presetSelectPre = 0;
int passOne = 0, passTwo = 0;
int editPulse = 255; //fade brightness when in in edit mode
int editPulseLo = 140;
int presetToggle = 1;
int presetValue = 20;
int fileOrderMode = 2;
int directionFilter = 0;
const int buttonOne = 13, buttonTwo = 12, buttonThree = 8;
//Mux pins
const int S0 = 2, S1 = 4, S2 = 7;
//Pots 'n CV's
//------------
//PORTAMENTO    8Bit
int kPortamento, kPortamentoPre;
int portamentoPotRaw = 0, portamentoPotRawPre = 0;
int portamentoPotClean, portamentoPotCleanPre, iPortamento;
//MIX    8Bit
int kMix, kMixPre;
int mixPotRaw = 0, mixPotRawPre = 0, mixPotMIDI = 0, mixPotMIDIPre = 0;
int mixPotClean, mixPotCleanPre, iMix;
int mixCVRaw = 0, mixCVRawPre = 0, mixCVMIDI = 0, mixCVMIDIPre = 0;
int mixCVClean, mixCVCleanPre, iMixCV = 40;
int mixDifference, mixCVScaled, mixCVThresh;
//
//SPEED    16Bit
int kSpeed, kSpeedPre, speedMSB, speedLSB;
int speedPotRaw = 0, speedPotRawPre = 0;
int speedPotClean, speedPotCleanPre, iSpeed;
int speedCVRaw = 0, speedCVRawPre = 0;
int speedCVClean, speedCVCleanPre, iSpeedCV = 40;
int speedDifference, speedCVScaled, speedCVThresh;
//
//PITCH    16Bit
int kPitch, kPitchPre, pitchMSB, pitchLSB;
int pitchPotRaw = 0, pitchPotRawPre = 0, pitchPotMIDI = 0, pitchPotMIDIPre = 0;
int pitchPotClean, pitchPotCleanPre, iPitch;
int pitchCVRaw = 0, pitchCVRawPre = 0, pitchCVMIDI = 0, pitchCVMIDIPre = 0;
int pitchCVClean, pitchCVCleanPre, iPitchCV = 40;
int pitchDifference, pitchCVScaled, pitchCVThresh;
//
//gSize    8Bit
int kgSize, kgSizePre;
int gSizePotRaw = 0, gSizePotRawPre = 0, gSizePotMIDI = 0, gSizePotMIDIPre = 0;
int gSizePotClean, gSizePotCleanPre, igSize;
int gSizeCVRaw = 0, gSizeCVRawPre = 0, gSizeCVMIDI = 0, gSizeCVMIDIPre = 0;
int gSizeCVClean, gSizeCVCleanPre, igSizeCV = 40;
int gSizeDifference, gSizeCVScaled, gSizeCVThresh;
//
//gRate    8Bit
int kgRate, kgRatePre;
int gRatePotRaw = 0, gRatePotRawPre = 0, gRatePotMIDI = 0, gRatePotMIDIPre = 0;
int gRatePotClean, gRatePotCleanPre, igRate;
int gRateCVRaw = 0, gRateCVRawPre = 0, gRateCVMIDI = 0, gRateCVMIDIPre = 0;
int gRateCVClean, gRateCVCleanPre, igRateCV = 40;
int gRateDifference, gRateCVScaled, gRateCVThresh;
//
//Start    16Bit
int kStart, kStartPre, startMSB, startLSB;
int startPotRaw = 0, startPotRawPre = 0;
int startPotClean, startPotCleanPre, iStart;
int startCVRaw = 0, startCVRawPre = 0;
int startCVClean, startCVCleanPre, iStartCV = 40;
int startDifference, startCVScaled, startCVThresh;
//
//loopE    16Bit
int kEnd, kEndPre, endMSB, endLSB;
int endPotRaw = 0, endPotRawPre = 0;
int endPotClean, endPotCleanPre, iEnd;
int endCVRaw = 0, endCVRawPre = 0;
int endCVClean, endCVCleanPre, iEndCV = 40;
int endDifference, endCVScaled, endCVThresh;
//
//FREEZE
int freezeRaw = 0, freezeRawPre = 0;
int freezeButtonToggle = 0;
//
//NEXT
int nextRaw = 0, nextRawPre = 0, nextCVFlag = 0;
//
//SHIFT BUTTON
int shiftState = 0, shiftRawPre = 0;
int shiftStatePre, shiftMode;
//
//PRESET TOGGLE CV
int presetToggleCVVal, presetToggleCVState = 0, presetToggleCV, presetToggleCVPre = 0;
int presetToggleCVRaw;
int presetToggleBreak = 0;
//RANGE
int rangeToggle;
//Buttons
int buttonVal, buttonState = 1;
int buttonOneVal, buttonOneState, buttonOneValPre;
int nextButtonToggle;
int buttonTwoVal, buttonTwoState, buttonTwoValPre;
int buttonThreeVal, buttonThreeState, buttonThreeValPre;
//EDIT MODE
int EDITMODE = 0;
int editModeState = 0;
int enterEdit;
int presetHoldState = 0;
int freezeState = 0;
int nextState = 0;
int rangeState = 0;
//Misc
int fadeDivision = 5, time = 20, firstPass = 0;
int readPause, readPauseEquals = 30;
int presetModeEnter = 0, presetHold = 0;
int freezeRepeat, rangeRepeat;
//Off sequence
//LED map
const int led1R = 9, led1G = 10, led1B = 11;
const int ledL = 5, ledR = 3, ledF = 6;
//ExternalMIDI
int extMidiVol, extMidiVolPre, extMidiVolOn = 0;
int extMidiPorta, extMidiPortaPre, extMidiPortaOn = 0;
int extMidiMix, extMidiMixPre, extMidiMixOn = 0;
//
int extMidiSpeed, extMidiSpeedPre, extMidiSpeedOn = 0;
int extMidiGsize, extMidiGsizePre, extMidiGsizeOn = 0;
int extMidiGrate, extMidiGratePre, extMidiGrateOn = 0;
//
int extMidiPitch, extMidiPitchPre, extMidiPitchOn = 0;
int extMidiEnd, extMidiEndPre, extMidiEndOn = 0;
int extMidiStart, extMidiStartPre, extMidiStartOn = 0;
//
unsigned long currentMillis, previousMillis = 0;
int randOn, randOff, randSelect;
int iMIDIMap = 0;
int bendMap, bendGate = 0;



void setup(){
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();
  MIDI.setHandleControlChange(HandleControlChange);
  MIDI.setHandleNoteOn(HandleNoteOn);
  MIDI.setHandlePitchBend(HandlePitchBend);
  Serial.begin(31250);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(led1R, OUTPUT);
  pinMode(led1G, OUTPUT);
  pinMode(led1B, OUTPUT);
  pinMode(ledL, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledF, OUTPUT);
  analogWrite(ledL, 255);
  analogWrite(ledR, 255);
  analogWrite(ledF, 255);
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
  pinMode(buttonThree, INPUT);
  fileOrderMode = 0;
  freezeButtonToggle = 1;
  freezeRepeat = 0;
  readPause = 1;
  off();
  firstPass = 0;
  time = 3;
  colourSweep();
  redOn();
  off();
  if(troubleShootMidi == 1){
    nextNext = 5;
  }
}

//==============================================================================================================
//==============================================================================================================

void loop(){
  gpioRead();
  if(nextNext < 3){
    bootUp();
  }
  readPause = readPause++;
  if(readPause > 90){
    readPause = 50;
  }

  MIDI.read();
  externalMidiPreset();
  readAllAnalog();
  ////onces when Csound starts
  if(nextNext == 3){
    nextNext = 4;
    initPotState();  
  }
  if(nextNext > 3){
    off();
  }
  if(nextNext == 4){
    nextNext = 5;
    if(switchBack == 1){
      switchBack = 0;
      globalOperation = 1;
    }
  }
  if(globalOperation == 1){ //OneShot mode active
    modeMidiNotes = 1;//for midi note messages mapped to oneshot samples
    oneShot();
  }
  if(globalOperation == 0){ //Normal mode active
    modeMidiNotes = 0;//Allow midi notes mapped to volt per 8ve range
    if(nextNext > 3){
      dontIgnore = 0;
      presetToggleCVolt();
      analogInterpret();
      basicButtons();
      advancedButtons();
      freeze();
      nextCV();
    }
    firstPass = 1;
  }
}

