void basicButtons(){
  //Freeze
  if((digitalRead(buttonTwo) == HIGH) && (freezeState == 0)){
    freezeButtonToggle = freezeButtonToggle++;
    if(freezeButtonToggle > 1){
      freezeButtonToggle = 0;
    }
    freezeState = 1;
  }
  if((digitalRead(buttonTwo) == LOW) && (freezeState == 1)){
    freezeState = 0;
  }
  //Next
  if((digitalRead(buttonThree) == HIGH) && (nextState == 0)){
    whiteOn();
    midiOUT(0xB0, utilityCC, 3);
    delay(80);
    midiOUT(0xB0, utilityCC, 4);
    nextState = 1;
  }
  if((digitalRead(buttonThree) == LOW) && (nextState == 1)){
    off();
    delay(10);
    nextState = 0;
  }
  //Recall
  if((digitalRead(buttonOne) == HIGH) && (presetHoldState == 1)){//Preset Hold
    off();
    hideLights = 1;
    delay(6);
    presetHold = 1;
    microsTimeThresh = 400;
    while(digitalRead(buttonOne) == HIGH){
      switch (presetToggle){
      case 1:
        presetFlash = 1;
        editMode();
        if(presetToggleCCPass == 0){
          midiOUT(0xB0, utilityCC, 12);
          presetToggleCCPass = 1;
        }
        break;
      case 2:
        presetFlash = 2;
        editMode();
        if(presetToggleCCPass == 0){
          midiOUT(0xB0, utilityCC, 13);
          presetToggleCCPass = 1;
        }
        break;
      case 3:
        presetFlash = 3;
        editMode();
        if(presetToggleCCPass == 0){
          midiOUT(0xB0, utilityCC, 14);
          presetToggleCCPass = 1;
        }
        break;
      }
    }
    hideLights = 0;
    presetHoldState = 0;
  }
  if((buttonTwoVal == LOW) && (presetHoldState == 0)){
    microsTimeThresh = 2000;
    presetToggleCCPass = 0;
    midiOUT(0xB0, utilityCC, 16);
    off();
    presetHoldState = 1;    
  }
  mux3();
  EDITMODE = (analogRead(A1)/512);
}
//
//
//
void advancedButtons(){
  mux3();
  if(EDITMODE == 1){
    flashHold = 1;
    off();
    delay(50);
    normalEdit = 0;
    while(flashHold == 1){
      if(((digitalRead(buttonOne) == LOW) || (digitalRead(buttonTwo) == LOW) || (digitalRead(buttonThree) == LOW)) && (normalEdit == 0)){
        off();
        delay(50);
        whiteOn();
        delay(60);
      }
      if(((analogRead(A1)/512) == 0) && (normalEdit == 0)){
        flashHold = 0;
        enterEdit = 1;
      }

      if((digitalRead(buttonOne) == HIGH) && (normalEdit == 0)){
        midiOUT(0xB0, 4, 0);
        midiOUT(0xB0, 5, 0);
        midiOUT(0xB0, 8, 127);
        int k = 255;
        while(k > 0){
          analogWrite(led1R, k);
          analogWrite(led1B, k);
          analogWrite(led1G, k);
          analogWrite(ledR, k);
          analogWrite(ledL, k);
          analogWrite(ledF, k);
          k = k--;
          delayMicroseconds(2500);
        }
        off();
        analogWrite(ledR, 255);
        analogWrite(ledL, 255);
        analogWrite(ledF, 255);
        normalEdit = 1;
      }
      mux3();
      if((digitalRead(buttonOne) == LOW) && (normalEdit == 1)){
        flashHold = 0;
        globalOperation = 1;
        oneShot2LoopFlag = 0;
        newMode = 0;
        firstOneShot = 0;
        midiOUT(0xB0, utilityCC, 24);// switch to oneshot mode
        delay(50);
      }
      newFiles();
    }
    if(newFilesFlag == 0){
      editModeState = 1;
    }
    newFilesFlag = 0;
    buttonTwoState = 0;
    t = 2500;          // Light pulse rate
    fadeOff = 1;       // Light pulse rate
    off();
    if(normalEdit == 1){
      normalEdit = 0;
      editModeState = 0;
    }
    while(editModeState == 1){
      mux1();
      presetSelect = map(analogRead(A1), 100, 700, 1, 3);
      presetSelect = constrain(presetSelect, 1, 3);
      if(abs(presetSelect - presetSelectPre) >= 1){
        presetFlag = 0;
        presetSelectPre = presetSelect;
        if(passOne == 1){
          passTwo = 1;
        }
      }
      if(passTwo == 0){
        presetSelect = 0;
      }
      switch (presetSelect) {
      case 0:
        presetFlash = 0;
        editMode();
        break;
      case 1:
        presetToggle = 1;
        presetValue = 18;
        presetFlash = 1;
        editMode();
        break;
      case 2:
        presetToggle = 2;
        presetValue = 19;
        presetFlash = 2;
        editMode();
        break;
      case 3:
        presetToggle = 3;
        presetValue = 20;
        presetFlash = 3;
        editMode();
        break;
      }
      passOne = 1;
      if(digitalRead(buttonThree) == HIGH){
        passOne = 0;
        passTwo = 0;
      }
      mux3();
      if((analogRead(A1)/512) == 1){
        whiteOn();
        delay(100);
        off();
        int e = 1;
        while(e == 1){
          if((analogRead(A1)/512) == 0){
            e = 0;
          }
          EDITMODE = 0;
          editModeState = 0;
          passOne = 0;
          passTwo = 0;
          readPause = 0;
          presetFlag = 1;
        }
      }
      //
      if((digitalRead(buttonOne) == HIGH)){ //Save to preset
        int k = 0;//Strobe to exit
        t = 25;
        off();
        while(k < 10){
          off();
          whiteOn();
          delay(t);
          off();
          delay(t);
          k = k++;
        }
        midiOUT(0xB0, utilityCC, presetValue);//Write to preset
        delay(40);
        midiOUT(0xB0, utilityCC, 22);
        editModeState = 0;
        passOne = 0;
        passTwo = 0;
        readPause = 0;
      }
      if((digitalRead(buttonTwo) == HIGH) && (directionFilter == 0)){ //File order Select
        int g = 1;
        while(g == 1){
          if(digitalRead(buttonThree) == LOW){
            analogWrite(ledL, 0);
            analogWrite(ledR, 0);
            analogWrite(ledF, 0);
            delay(40);
            analogWrite(ledL, 255);
            analogWrite(ledR, 255);
            analogWrite(ledF, 255);
            delay(40);
          }
          if(digitalRead(buttonThree) == HIGH){
            scatterToggle = 1;
            analogWrite(led1R, 220);
            analogWrite(led1G, 255);
            analogWrite(led1B, 220);
          }
          if(digitalRead(buttonTwo) == LOW){
            break;
          }
        }
        directionFilter = 1;
      }
      if((digitalRead(buttonTwo) == LOW) && (directionFilter == 1)){
        delay(60);
        directionFilter = 0;
        if(scatterToggle == 0){
          ledStep = 1;
          directionGate = 1;
          fileOrderMode = fileOrderMode++;
          if(fileOrderMode > 2){
            fileOrderMode = 0;
          }
        }
        if(fileOrderMode == 0){
          if(directionGate == 1){
            midiOUT(0xB0, utilityCC, 5);
            directionGate = 0;
          }
          Forward();
        }
        if(fileOrderMode == 1){
          if(directionGate == 1){
            midiOUT(0xB0, utilityCC, 6);
            directionGate = 0;
          }
          Backward();
        }
        if(fileOrderMode == 2){
          if(directionGate == 1){
            midiOUT(0xB0, utilityCC, 7);
            directionGate = 0;
          }
          Random();
        }
      }
      //Range Toggle
      if((digitalRead(buttonThree) == HIGH) && (rangeState == 0)){
        int h = 1;
        while(h == 1){
          if(digitalRead(buttonTwo) == LOW){
            off();
            whiteOn();
            delay(40);
            off();
            delay(40);
          }
          if(digitalRead(buttonTwo) == HIGH){
            scatterToggle = 1;
            analogWrite(led1R, 220);
            analogWrite(led1G, 255);
            analogWrite(led1B, 220);
          }
          if(digitalRead(buttonThree) == LOW){
            break;
          }
        }
        rangeState = 1;
      }
      if((digitalRead(buttonThree) == LOW) && (rangeState == 1)){
        delay(40);
        rangeState = 0;
        if(scatterToggle == 0){
          rangeControl = rangeControl++;
          if(rangeControl > 2){
            rangeControl = 0;
          }
          if(rangeControl == 0){//Extended tracking
            presetSelect = 0;
            rangeLight = 0;
            midiOUT(0xB0, utilityCC, 10);
            off();
            analogWrite(led1R, 0);
            analogWrite(led1G, 255);
            analogWrite(led1B, 255);
            off();
          }
          if(rangeControl == 1){//volt per octave
            presetSelect = 0;
            rangeLight = 1;
            midiOUT(0xB0, utilityCC, 8);
            off();
            analogWrite(led1R, 210);
            analogWrite(led1G, 255);
            analogWrite(led1B, 0);
            off();
          }
          if(rangeControl == 2){//Normal range aliasing
            presetSelect = 0;
            rangeLight = 2;
            midiOUT(0xB0, utilityCC, 9);
            off();
            analogWrite(led1R, 0);
            analogWrite(led1G, 210);
            analogWrite(led1B, 255);
            off();
          }
        }
      }
    }
  }
}
















