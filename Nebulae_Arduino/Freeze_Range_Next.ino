void freeze(){
  if(abs((freezeRaw/512) - freezeRawPre) >= 1){
    if(freezeRaw > 512){
      freezeButtonToggle = freezeButtonToggle++; 
      if(freezeButtonToggle > 1){
        freezeButtonToggle = 0;
      }
    }
    freezeRawPre = freezeRaw/512;   
  }  
  if((freezeButtonToggle == 0) && (freezeRepeat == 1)){
    midiOUT(0xB0, utilityCC, 1);
    analogWrite(ledF, 0);
    freezeRepeat = 0;
  }
  if((freezeButtonToggle == 1) && (freezeRepeat == 0)){
    midiOUT(0xB0, utilityCC, 2);
    analogWrite(ledF, 255);
    freezeRepeat = 1;
  }
}

void range(){
  if((rangeToggle == 0) && (rangeRepeat == 1)){
    off();
    time = 2;
    midiOUT(0xB0, 50, 0);
    for(int i = 255; i >= 0; i -=10){
      analogWrite(led1B, i);
      delay(time);
    }
    for(int i = 255; i >= 0; i -=10){
      delay(time);
    }
    for(int i = 0; i <= 255; i +=10){
      analogWrite(led1B, i);
      delay(time);
    }
    for(int i = 0; i <= 255; i +=10){
      delay(time);
    }
    rangeRepeat = 0;
  }
  if((rangeToggle == 1) && (rangeRepeat == 0)){
    off();
    time = 2;
    midiOUT(0xB0, 50, 127);
    for(int i = 255; i >= 0; i -=10){
      analogWrite(led1R, i);
      delay(time);
    }
    for(int i = 255; i >= 0; i -=10){
      delay(time);
    }
    for(int i = 0; i <= 255; i +=10){
      analogWrite(led1R, i);
      delay(time);
    }
    for(int i = 0; i <= 255; i +=10){
      delay(time);
    }
    rangeRepeat = 1;
  }
}

void nextCV(){
  if(((nextRaw/512) == 1) && (nextCVFlag == 0)){
    whiteOn();
    midiOUT(0xB0, utilityCC, 3);
    delay(80);
    midiOUT(0xB0, utilityCC, 4);
    nextCVFlag = 1;
  }
  if(((nextRaw/512) == 0) && (nextCVFlag == 1)){
    off();
    nextCVFlag = 0;
  }
}
