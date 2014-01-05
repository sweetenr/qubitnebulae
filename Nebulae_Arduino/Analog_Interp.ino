void analogInterpret(){
  //======
  //PORTAMENTO
  //======
  kPortamento = portamentoPotRaw;
  if(abs(kPortamento - kPortamentoPre) >= 8){      //Movement sensor ammount
    iPortamento = 0;
    kPortamentoPre = kPortamento;
  }
  iPortamento = iPortamento++;
  if(iPortamento > 40){
    iPortamento = 30;
  }
  if(iPortamento <= 29){
    if(readPause > readPauseEquals){
      midiOUT(0xB0, 70, kPortamento/8);
    }
  }
  //======
  //MIX
  //======
  //============================ Mix CV Clean ===================================
  mixCVClean = mixCVRaw;
  if(abs(mixCVClean - mixCVCleanPre) >= 30){
    iMixCV = 0;//counter reset
    mixCVCleanPre = mixCVClean;
  }
  iMixCV = iMixCV++;
  if(iMixCV > countReturn){
    iMixCV = countVal;
  }
  if(((mixCVRaw/8) >= 45) && ((mixCVRaw/8) <= 55)){//Ignore Range between 46 and 51
    mixCVThresh = 1;
  }
  if(((mixCVRaw/8) < 45) || ((mixCVRaw/8) > 55)){
    mixCVThresh = 0;
  }
  //------------------------------ Mix Combine -----------------------------------
  mixCVScaled = map(mixCVRaw, 0, 1023, -511, 512);
  if((iMixCV > countThresh) && (mixCVThresh == 1)){ 
    mixCVScaled = 0;
  }
  kMix = constrain((mixPotRaw + mixCVScaled), 0, 1023);
  //================================ Mix MIDI =====================================
  if(abs(kMix - kMixPre) >= 8){//Movement sensor ammount
    iMix = 0;
    kMixPre = kMix;
  }
  iMix = iMix++;
  if(iMix > 40){
    iMix = 30;
  }
  if(iMix <= 29){
    if(readPause > readPauseEquals){
      midiOUT(0xB0, 8, kMix/8);
    }
  }
  //======
  //SPEED
  //======
  //============================ Speed CV Clean ===================================
  speedCVClean = speedCVRaw;
  if(abs(speedCVClean - speedCVCleanPre) >= 30){
    iSpeedCV = 0;//counter reset
    speedCVCleanPre = speedCVClean;
  }
  iSpeedCV = iSpeedCV++;
  if(iSpeedCV > countReturn){
    iSpeedCV = countVal;//Ignore count to 200
  }
  if(((speedCVRaw/8) >= 45) && ((speedCVRaw/8) <= 55)){//Ignore Range between 46 and 51
    speedCVThresh = 1;
  }
  if(((speedCVRaw/8) < 45) || ((speedCVRaw/8) > 55)){
    speedCVThresh = 0;
  }
  //------------------------------ Speed Combine -----------------------------------
  speedCVScaled = map(speedCVRaw, 0, 1023, -511, 512);
  if((iSpeedCV > countThresh) && (speedCVThresh == 1)){ 
    speedCVScaled = 0;
  }
  kSpeed = constrain((speedPotRaw + speedCVScaled), 0, 1023);
  speedLEDlo = map(kSpeed, 0, 511, 0, 255);
  speedLEDlo = constrain(speedLEDlo, 0, 255);
  speedLEDhi = map(kSpeed, 512, 1023, 255, 0);
  speedLEDhi = constrain(speedLEDhi, 0, 255);
  if(nextNext > 3){
    analogWrite(ledL, speedLEDlo);
    analogWrite(ledR, speedLEDhi);
  }
  //================================ Speed MIDI =====================================
  if(abs(kSpeed - kSpeedPre) >= 8){//Movement sensor ammount
    iSpeed = 0;
    kSpeedPre = kSpeed;
  }
  iSpeed = iSpeed++;
  if(iSpeed > 40){
    iSpeed = 30;
  }
  if(iSpeed <= 29){
    speedMSB = (kSpeed >> 3) & 0x7F;//10Bit to 14Bit
    speedLSB = (kSpeed & 0x7) << 4;
    if(readPause > readPauseEquals){
      midiOUT(0xB0, 1, speedMSB);
      midiOUT(0xB0, 2, speedLSB);
    }
  }
  //======
  //PITCH
  //======
  //============================ Pitch CV Clean ===================================
  pitchCVClean = pitchCVRaw;
  if(abs(pitchCVClean - pitchCVCleanPre) >= 30){
    iPitchCV = 0;//counter reset
    pitchCVCleanPre = pitchCVClean;
  }
  iPitchCV = iPitchCV++;
  if(iPitchCV > countReturn){
    iPitchCV = countVal;//Ignore count to 200
  }
  kPitch = constrain((pitchPotRaw + pitchCVRaw), 0, 1023);
  //================================ Pitch MIDI =====================================
  if(abs(kPitch - kPitchPre) >= 8){//Movement sensor ammount
    iPitch = 0;
    iMIDIMap = 0;
    kPitchPre = kPitch;
  }
  iPitch = iPitch++;
  if(iPitch > 40){
    iPitch = 30;
  }
  if(iMIDIMap == 1){
    kPitch = pitchMap;
  }
  kPitch = kPitch + bendMap;
  if((iPitch <= 29) || (bendGate == 1)){
    pitchMSB = (kPitch >> 3) & 0x7F;
    pitchLSB = (kPitch & 0x7) << 4;
    if(readPause > readPauseEquals){
      midiOUT(0xB0, 15, pitchMSB);
      midiOUT(0xB0, 16, pitchLSB);
    }
  }
  //======
  //GSIZE
  //======
  //============================ GSize CV Clean ===================================
  gSizeCVClean = gSizeCVRaw;
  if(abs(gSizeCVClean - gSizeCVCleanPre) >= 30){
    igSizeCV = 0;//counter reset
    gSizeCVCleanPre = gSizeCVClean;
  }

  igSizeCV = igSizeCV++;
  if(igSizeCV > countReturn){
    igSizeCV = countVal;//Ignore count to 200
  }
  kgSize = constrain((gSizePotRaw + gSizeCVRaw), 0, 1023);
  //================================ GSize MIDI =====================================
  if(abs(kgSize - kgSizePre) >= 8){//Movement sensor ammount
    igSize = 0;
    kgSizePre = kgSize;
  }
  igSize = igSize++;
  if(igSize > 40){
    igSize = 30;
  }
  if(igSize <= 29){
    if(readPause > readPauseEquals){
      midiOUT(0xB0, 4, kgSize/8);
    }
  }
  //======
  //GRATE
  //======
  if(scatterState == 0){
    //============================ GRate CV Clean ===================================
    gRateCVClean = gRateCVRaw;
    if(abs(gRateCVClean - gRateCVCleanPre) >= 30){
      igRateCV = 0;//counter reset
      gRateCVCleanPre = gRateCVClean;
    }
    igRateCV = igRateCV++;
    if(igRateCV > countReturn){
      igRateCV = countVal;//Ignore count to 200
    }
    kgRate = constrain((gRatePotRaw + gRateCVRaw), 0, 1023);
    //================================ GRate MIDI =====================================
    if(abs(kgRate - kgRatePre) >= 8){//Movement sensor ammount
      igRate = 0;
      kgRatePre = kgRate;
    }
    igRate = igRate++;
    if(igRate > 40){
      igRate = 30;
    }
    if(igRate <= 29){
      if(readPause > readPauseEquals){
        midiOUT(0xB0, 5, kgRate/8);
      }
    }
  }
  else if(scatterState == 1){
    gRateCVClean = gRateCVRaw;
    if(abs(gRateCVClean - gRateCVCleanPre) >= 30){
      igRateCV = 0;//counter reset
      gRateCVCleanPre = gRateCVClean;
    }
    igRateCV = igRateCV++;
    if(igRateCV > countReturn){
      igRateCV = countVal;//Ignore count to 200
    }
    scatter = (random(scatterRange)) - (scatterRange/2);
    kgRate = constrain((gRatePotRaw + gRateCVRaw + scatter), 0, 1023);
    midiOUT(0xB0, 5, kgRate/8);
  }
  //======
  //END
  //======
  //============================ End CV Clean ===================================
  endCVClean = endCVRaw;
  if(abs(endCVClean - endCVCleanPre) >= 30){
    iEndCV = 0;//counter reset
    endCVCleanPre = endCVClean;
  }
  iEndCV = iEndCV++;
  if(iEndCV > countReturn){
    iEndCV = countVal;//Ignore count to 200
  }
  kEnd = constrain((endPotRaw + endCVRaw), 0, 1023);
  //================================ End MIDI =====================================
  if(abs(kEnd - kEndPre) >= 8){//Movement sensor ammount
    iEnd = 0;
    kEndPre = kEnd;
  }
  iEnd = iEnd++;
  if(iEnd > 40){
    iEnd = 30;
  }
  if(iEnd <= 29){
    endMSB = (kEnd >> 3) & 0x7F;//10Bit to 14Bit
    endLSB = (kEnd & 0x7) << 4;
    if(readPause > readPauseEquals){
      midiOUT(0xB0, 11, endMSB);
      midiOUT(0xB0, 12, endLSB);
    }
  }
  //======
  //START
  //======
  //============================ Start CV Clean ===================================
  startCVClean = startCVRaw;
  if(abs(startCVClean - startCVCleanPre) >= 30){
    iStartCV = 0;//counter reset
    startCVCleanPre = startCVClean;
  }
  iStartCV = iStartCV++;
  if(iStartCV > countReturn){
    iStartCV = countVal;//Ignore count to 200
  }
  kStart = constrain((startPotRaw + startCVRaw), 0, 1023);
  //================================ Start MIDI =====================================
  if(abs(kStart - kStartPre) >= 8){//Movement sensor ammount
    iStart = 0;
    kStartPre = kStart;
  }
  iStart = iStart++;
  if(iStart > 40){
    iStart = 30;
  }
  if(iStart <= 29){
    startMSB = (kStart >> 3) & 0x7F;//10Bit to 14Bit
    startLSB = (kStart & 0x7) << 4;
    if(readPause > readPauseEquals){
      midiOUT(0xB0, 9, startMSB);
      midiOUT(0xB0, 10, startLSB);
    }
  }
}


