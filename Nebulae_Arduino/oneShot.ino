int oneShotBank = 0, shotBankFlag = 0;
int b1oneShotFlag = 0, b2oneShotFlag = 0, b3oneShotFlag = 0;
int smp1Flag, smp2Flag, smp3Flag, smp4Flag, smp5Flag, smp6Flag, smp7Flag, smp8Flag, smpStopFlag;
int rest = 20, showColour = 30;
unsigned long returnNormalMillis, returnNormalMillisPre = 0;
int returnNormalCounter = 0;
void oneShot(){
  if(nextNext < 3){
    bootUp();
  }
  while(newMode == 0){
    gpioRead();
    if(abs(gpioStateChange - gpioStateChangePre) >= 1){
      gpioStateChangePre = gpioStateChange;
      speedStates();
      newMode = 1;
      delay(500);
    }
  }
  readAllAnalog();
  speedPotRaw = constrain((speedPotRaw+pitchCVRaw), 0, 1023);
  smp1MSB = (speedPotRaw >> 3) & 0x7F;
  smp1LSB = (speedPotRaw & 0x7) << 4;
  //
  portamentoPotRaw = constrain((portamentoPotRaw+pitchCVRaw), 0, 1023);
  smp2MSB = (portamentoPotRaw >> 3) & 0x7F;
  smp2LSB = (portamentoPotRaw & 0x7) << 4;
  //
  pitchPotRaw = constrain((pitchPotRaw+pitchCVRaw), 0, 1023);
  smp3MSB = (pitchPotRaw >> 3) & 0x7F;
  smp3LSB = (pitchPotRaw & 0x7) << 4;
  //
  mixPotRaw = constrain((mixPotRaw+pitchCVRaw), 0, 1023);
  smp4MSB = (mixPotRaw >> 3) & 0x7F;
  smp4LSB = (mixPotRaw & 0x7) << 4;
  //
  gSizePotRaw = constrain((gSizePotRaw+pitchCVRaw), 0, 1023);
  smp5MSB = (gSizePotRaw >> 3) & 0x7F;
  smp5LSB = (gSizePotRaw & 0x7) << 4;
  //
  gRatePotRaw = constrain((gRatePotRaw+pitchCVRaw), 0, 1023);
  smp6MSB = (gRatePotRaw >> 3) & 0x7F;
  smp6LSB = (gRatePotRaw & 0x7) << 4;
  //
  startPotRaw = constrain((startPotRaw+pitchCVRaw), 0, 1023);
  smp7MSB = (startPotRaw >> 3) & 0x7F;
  smp7LSB = (startPotRaw & 0x7) << 4;
  //
  endPotRaw = constrain((endPotRaw+pitchCVRaw), 0, 1023);
  smp8MSB = (endPotRaw >> 3) & 0x7F;
  smp8LSB = (endPotRaw & 0x7) << 4;
  //
  mux3();
  if(((analogRead(A1)/512) == 1) && (shotBankFlag == 0)  && (digitalRead(buttonOne) == LOW) && (digitalRead(buttonTwo) == LOW) && (digitalRead(buttonThree) == LOW)){//Read edit button to cycle Bank
    shotBankFlag = 1;
    delay(10);
    oneShotBank = oneShotBank++;
    if(oneShotBank > 2){
      oneShotBank = 0;
    }
  }
  mux3();
  if(((analogRead(A1)/512) == 0) && (shotBankFlag == 1)){
    shotBankFlag = 0;
    delay(10);
  }
  if(oneShotBank == 0){//Bank number Display
    analogWrite(ledL, 0);
    analogWrite(ledR, 255);
    analogWrite(ledF, 255);
  }
  if(oneShotBank == 1){
    analogWrite(ledL, 255);
    analogWrite(ledR, 0);
    analogWrite(ledF, 255);
  }
  if(oneShotBank == 2){
    analogWrite(ledL, 255);
    analogWrite(ledR, 255);
    analogWrite(ledF, 0);
  }
  if((digitalRead(buttonOne) == HIGH) && (b1oneShotFlag == 0) && ((analogRead(A1)/512) == 0)){//Button One oneshot trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    if(dontIgnore == 0){
      speedStates();
    }
    midiOUT(0xB0, 1+(oneShotBank*3), 127);
    delay(rest);
    b1oneShotFlag = 1;
    if(oneShotBank == 0){
      redOn();
      delay(showColour);
      off();
    }
    else if(oneShotBank == 1){
      greenOn();
      delay(showColour);
      off();
    }
    else if(oneShotBank == 2){
      magentaOn();
      delay(showColour);
      off();
    }
  }
  if((digitalRead(buttonOne) == LOW) && (b1oneShotFlag == 1)){
    midiOUT(0xB0, 1+(oneShotBank*3), 0);
    b1oneShotFlag = 0;
  }
  if((digitalRead(buttonTwo) == HIGH) && (b2oneShotFlag == 0) && ((analogRead(A1)/512) == 0)){//Button Two oneshot trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    if(dontIgnore == 0){
      speedStates();
    }
    midiOUT(0xB0, 2+(oneShotBank*3), 127);
    delay(rest);
    b2oneShotFlag = 1;
    if(oneShotBank == 0){
      analogWrite(led1R, 0);
      analogWrite(led1G, 210);
      analogWrite(led1B, 255);
      delay(showColour);
      off();
    }
    else if(oneShotBank == 1){
      cyanOn();
      delay(showColour);
      off();
    }
    else if(oneShotBank == 2){
      whiteOn();
      delay(showColour);
      off();
    }
  }
  if((digitalRead(buttonTwo) == LOW) && (b2oneShotFlag == 1)){
    midiOUT(0xB0, 2+(oneShotBank*3), 0);
    b2oneShotFlag = 0;
  }
  if((digitalRead(buttonThree) == HIGH) && (b3oneShotFlag == 0) && ((analogRead(A1)/512) == 0)){//Button Three oneshot trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    if(dontIgnore == 0){
      speedStates();
    }
    if(oneShotBank < 2){
      midiOUT(0xB0, 3+(oneShotBank*3), 127);
      delay(rest);
    }
    if(oneShotBank == 2){
      midiOUT(0xB0, 28, 127);
      delay(rest);
    }
    b3oneShotFlag = 1;
    if(oneShotBank == 0){
      yellowOn();
      delay(showColour);
      off();
    }
    else if(oneShotBank == 1){
      blueOn();
      delay(showColour);
      off();
    }
    else if(oneShotBank == 2){
      whiteOn();
      delay(showColour);
      off();
    }
  }
  if((digitalRead(buttonThree) == LOW) && (b3oneShotFlag == 1)){
    b3oneShotFlag = 0;
    if(oneShotBank < 2){
      midiOUT(0xB0, 3+(oneShotBank*3), 0);
    }  
    if(oneShotBank == 2){
      midiOUT(0xB0, 28, 0);
    }
  }
  if((presetToggleCVRaw > 511) && (smp1Flag == 0)){//Sample 1 gate trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    smp1Flag = 1;
    midiOUT(0xB0, 1, 0);
    midiOUT(0xB0, 1, 127);
    delay(rest);

    redOn();
    delay(showColour);
    off();
  }
  if((presetToggleCVRaw <= 511) && (smp1Flag == 1)){
    smp1Flag = 0;
    midiOUT(0xB0, 1, 0);
  }
  if((freezeRaw > 511) && (smp2Flag == 0)){//Sample 2 gate trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    smp2Flag = 1;
    midiOUT(0xB0, 2, 0);
    midiOUT(0xB0, 2, 127);
    delay(rest);
    analogWrite(led1R, 0);
    analogWrite(led1G, 210);
    analogWrite(led1B, 255);
    delay(showColour);
    off();
  }
  if((freezeRaw <= 511) && (smp2Flag == 1)){
    smp2Flag = 0;
    midiOUT(0xB0, 2, 0);
  }

  if((nextRaw > 511) && (smp3Flag == 0)){//Sample 3 gate trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    smp3Flag = 1;
    midiOUT(0xB0, 3, 0);
    midiOUT(0xB0, 3, 127);
    delay(rest);
    yellowOn();
    delay(showColour);
    off();
  }
  if((nextRaw <= 511) && (smp3Flag == 1)){
    smp3Flag = 0;
    midiOUT(0xB0, 3, 0);
  }
  if((mixCVRaw > 511) && (smp4Flag == 0)){//Sample 4 gate trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    smp4Flag = 1;
    midiOUT(0xB0, 4, 0);
    midiOUT(0xB0, 4, 127);
    delay(rest);
    greenOn();
    delay(showColour);
    off();
  }
  if((mixCVRaw <= 511) && (smp4Flag == 1)){
    smp4Flag = 0;
    midiOUT(0xB0, 4, 0);
  }
  if((gSizeCVRaw > 511) && (smp5Flag == 0)){//Sample 5 gate trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    smp5Flag = 1;
    midiOUT(0xB0, 5, 0);
    midiOUT(0xB0, 5, 127);
    delay(rest);
    cyanOn();
    delay(showColour);
    off();
  }
  if((gSizeCVRaw <= 511) && (smp5Flag == 1)){
    smp5Flag = 0;
    midiOUT(0xB0, 5, 0);
  }
  if((gRateCVRaw > 511) && (smp6Flag == 0)){//Sample 6 gate trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    smp6Flag = 1;
    midiOUT(0xB0, 6, 0);
    midiOUT(0xB0, 6, 127);
    delay(rest);

    blueOn();
    delay(showColour);
    off();
  }
  if((gRateCVRaw <= 511) && (smp6Flag == 1)){
    smp6Flag = 0;
    midiOUT(0xB0, 6, 0);
  }
  if((startCVRaw > 511) && (smp7Flag == 0)){//Sample 7 gate trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    smp7Flag = 1;
    midiOUT(0xB0, 7, 0);
    midiOUT(0xB0, 7, 127);
    delay(rest);
    magentaOn();
    delay(showColour);
    off();
  }
  if((startCVRaw <= 511) && (smp7Flag == 1)){
    smp7Flag = 0;
    midiOUT(0xB0, 7, 0);
  }
  if((endCVRaw > 511) && (smp8Flag == 0)){//Sample 8 gate trigger
    if(midiMute == 1){
      midiMute = 0;
    }
    smp8Flag = 1;
    midiOUT(0xB0, 8, 0);
    midiOUT(0xB0, 8, 127);
    delay(rest);
    analogWrite(led1R, 210);
    analogWrite(led1G, 255);
    analogWrite(led1B, 0);
    delay(showColour);
    off();
  }
  if((endCVRaw <= 511) && (smp8Flag == 1)){
    smp8Flag = 0;
    midiOUT(0xB0, 8, 0);
  }
  //CV Kill all playing
  if((speedCVRaw > 511) && (smpStopFlag == 0)){//Sample 8 gate trigger
    smpStopFlag = 1;
    midiOUT(0xB0, 28, 0);
    midiOUT(0xB0, 28, 127);
    delay(50);
    midiOUT(0xB0, 28, 0);
    delay(rest);
    whiteOn();
    delay(showColour);
    off();
  }
  if((speedCVRaw <= 511) && (smpStopFlag == 1)){
    smpStopFlag = 0;
    midiOUT(0xB0, 28, 0);
  }
  //Sample Pitch controls
  if(abs(speedPotRaw - speedPotRawPre) >= 8){
    speedPotRawPre = speedPotRaw;
    iSpeed = 0;
  }
  iSpeed = iSpeed++;
  if(iSpeed > 40){
    iSpeed = 30;
  }
  if(iSpeed <= 29){
    midiOUT(0xB0, 9, smp1MSB);
    midiOUT(0xB0, 10, smp1LSB);
  }
  //
  if(abs(portamentoPotRaw - portamentoPotRawPre) >= 8){
    portamentoPotRawPre = portamentoPotRaw;
    iPortamento = 0;
  }
  iPortamento = iPortamento++;
  if(iPortamento > 40){
    iPortamento = 30;
  }
  if(iPortamento <= 29){
    midiOUT(0xB0, 11, smp2MSB);
    midiOUT(0xB0, 12, smp2LSB);
  }
  //
  if(abs(pitchPotRaw - pitchPotRawPre) >= 8){
    pitchPotRawPre = pitchPotRaw;
    iPitch = 0;
  }
  iPitch = iPitch++;
  if(iPitch > 40){
    iPitch = 30;
  }
  if(iPitch <= 29){
    midiOUT(0xB0, 13, smp3MSB);
    midiOUT(0xB0, 14, smp3LSB);
  }
  //
  if(abs(mixPotRaw - mixPotRawPre) >= 8){
    mixPotRawPre = mixPotRaw;
    iMix = 0;
  }
  iMix = iMix++;
  if(iMix > 40){
    iMix = 30;
  }
  if(iMix <= 29){
    midiOUT(0xB0, 15, smp4MSB);
    midiOUT(0xB0, 16, smp4LSB);
  }
  //
  if(abs(gSizePotRaw - gSizePotRawPre) >= 8){
    gSizePotRawPre = gSizePotRaw;
    igSize = 0;
  }
  igSize = igSize++;
  if(igSize > 40){
    igSize = 30;
  }
  if(igSize <= 29){
    midiOUT(0xB0, 17, smp5MSB);
    midiOUT(0xB0, 18, smp5LSB);
  }
  //
  if(abs(gRatePotRaw - gRatePotRawPre) >= 8){
    gRatePotRawPre = gRatePotRaw;
    igRate = 0;
  }
  igRate = igRate++;
  if(igRate > 40){
    igRate = 30;
  }
  if(igRate <= 29){
    midiOUT(0xB0, 19, smp6MSB);
    midiOUT(0xB0, 20, smp6LSB);
  }
  //
  if(abs(startPotRaw - startPotRawPre) >= 8){
    startPotRawPre = startPotRaw;
    iStart = 0;
  }
  iStart = iStart++;
  if(iStart > 40){
    iStart = 30;
  }
  if(iStart <= 29){
    midiOUT(0xB0, 21, smp7MSB);
    midiOUT(0xB0, 22, smp7LSB);
  }
  //
  if(abs(endPotRaw - endPotRawPre) >= 8){
    endPotRawPre = endPotRaw;
    iEnd = 0;
  }
  iEnd = iEnd++;
  if(iEnd > 40){
    iEnd = 30;
  }
  if(iEnd <= 29){
    midiOUT(0xB0, 24, smp8MSB);
    midiOUT(0xB0, 25, smp8LSB);
  }
  //
  returnNormalCounter = 0;
  ledChange1 = 255;
  if(((analogRead(A1)/512) == 1) && (digitalRead(buttonOne) == LOW) && (digitalRead(buttonTwo) == LOW) && (digitalRead(buttonThree) == HIGH)){
    int reloadHold = 1;
    while(reloadHold == 1){
      analogWrite(ledL, 255);
      analogWrite(ledR, 255);
      analogWrite(ledF, 255);
      magentaOn();
      if(((analogRead(A1)/512) == 0) && (digitalRead(buttonThree) == LOW)){
        midiOUT(0xB0, 23, 28);
        globalOperation = 0;
        reloadHold = 0;
        readPause = 0;
        editModeState = 0;
        gpioStateChange = 0;
        nextNext = 0;
        oneShotBank = 0;
        switchBack = 1;
        midiMute = 1;
        break;
      }
    }
  }

  while(((analogRead(A1)/512) == 1) && (digitalRead(buttonOne) == HIGH) && (digitalRead(buttonTwo) == LOW) && (digitalRead(buttonThree) == LOW)){//EXIT ONE SHOT MODE
    if(((analogRead(A1)/512) == 1) && (digitalRead(buttonOne) == HIGH)){
      analogWrite(ledL, 255);
      analogWrite(ledR, 255);
      analogWrite(ledF, 255);
      midiOUT(0xB0, 23, 26);//Return to looping mode
      globalOperation = 0;
      firstOneShot = 0;
      readPause = 0;
      editModeState = 0;
      gpioStateChange = 2;
      nextNext = 2;
      oneShotBank = 0;
      break;
    }
  }
}


void speedStates(){
  readAllAnalog();
  delay(5);
  //
  smp1MSB = (speedPotRaw >> 3) & 0x7F;
  smp1LSB = (speedPotRaw & 0x7) << 4;
  //
  smp2MSB = (portamentoPotRaw >> 3) & 0x7F;
  smp2LSB = (portamentoPotRaw & 0x7) << 4;
  //
  smp3MSB = (pitchPotRaw >> 3) & 0x7F;
  smp3LSB = (pitchPotRaw & 0x7) << 4;
  //
  smp4MSB = (mixPotRaw >> 3) & 0x7F;
  smp4LSB = (mixPotRaw & 0x7) << 4;
  //
  smp5MSB = (gSizePotRaw >> 3) & 0x7F;
  smp5LSB = (gSizePotRaw & 0x7) << 4;
  //
  smp6MSB = (gRatePotRaw >> 3) & 0x7F;
  smp6LSB = (gRatePotRaw & 0x7) << 4;
  //
  smp7MSB = (startPotRaw >> 3) & 0x7F;
  smp7LSB = (startPotRaw & 0x7) << 4;
  //
  smp8MSB = (endPotRaw >> 3) & 0x7F;
  smp8LSB = (endPotRaw & 0x7) << 4;
  //
  midiOUT(0xB0, 9, smp1MSB);
  midiOUT(0xB0, 10, smp1LSB);
  delay(2);
  //
  midiOUT(0xB0, 11, smp2MSB);
  midiOUT(0xB0, 12, smp2LSB);
  delay(2);
  //
  midiOUT(0xB0, 13, smp3MSB);
  midiOUT(0xB0, 14, smp3LSB);
  delay(2);
  //
  midiOUT(0xB0, 15, smp4MSB);
  midiOUT(0xB0, 16, smp4LSB);
  delay(2);
  //
  midiOUT(0xB0, 17, smp5MSB);
  midiOUT(0xB0, 18, smp5LSB);
  delay(2);
  //
  midiOUT(0xB0, 19, smp6MSB);
  midiOUT(0xB0, 20, smp6LSB);
  delay(2);
  //
  midiOUT(0xB0, 21, smp7MSB);
  midiOUT(0xB0, 22, smp7LSB);
  delay(2);
  //
  midiOUT(0xB0, 24, smp8MSB);
  midiOUT(0xB0, 25, smp8LSB);
  delay(2);
}












