void editMode(){//Lighting Sequences
  //----------------------------
  if(scatterToggle == 1){
    scatterState = scatterState++;
    if(scatterState > 1){
      scatterState = 0;
    }
    if(scatterState == 0){
      magentaOn();
      delay(1000);
      editModeState = 0;
    }
    if(scatterState == 1){
      int j = 0;
      while(j < 10){
        magentaOn();
        delay(50);
        off();
        delay(50);
        j = j++;
      }
      editModeState = 0;
    }
    scatterToggle = 0;
  }
  //
  if(hideLights == 0){
    if(fileOrderMode == 0){
      Forward();
    }
    else if(fileOrderMode == 1){
      Backward();
    }
    else if(fileOrderMode == 2){
      Random();
    }
  }
  //
  faderMillis = micros();
  if((faderMillis - faderMillisPre) > microsTimeThresh){
    if(ledBrightness > 254){
      alternateWhite = alternateWhite++;
      if(alternateWhite > 1){
        alternateWhite = 0;
      }
      brightnessDir = 0;
    }
    if(ledBrightness < 1){
      brightnessDir = 1;
    }
    faderMillisPre = faderMillis;
    if(brightnessDir == 1){ 
      ledBrightness = ledBrightness++;
    }
    if(brightnessDir == 0){
      ledBrightness = ledBrightness--;
    }
  }
  if(presetFlash == 0){
    microsTimeThresh = 300;
    if(alternateWhite == 1){
      if(digitalRead(buttonThree) == LOW){
      }
      if(digitalRead(buttonThree) == HIGH){
        microsTimeThresh = 5;
      }
      analogWrite(led1R, ledBrightness);
      analogWrite(led1G, ledBrightness);
      analogWrite(led1B, ledBrightness);
    }
    if(alternateWhite == 0){
      microsTimeThresh = 2200;
      if(rangeLight == 0){
        analogWrite(led1R, ledBrightness);
        analogWrite(led1G, 255);
        analogWrite(led1B, 255);
      }
      if(rangeLight == 1){
        redAltered = map(ledBrightness, 0, 255, 210, 255);
        greenAltered = 255;
        blueAltered = ledBrightness;
        analogWrite(led1R, redAltered);
        analogWrite(led1G, greenAltered);
        analogWrite(led1B, blueAltered);
      }
      if(rangeLight == 2){
        redAltered = ledBrightness;
        greenAltered = map(ledBrightness, 0, 255, 210, 255);
        blueAltered = 255;
        analogWrite(led1R, redAltered);
        analogWrite(led1G, greenAltered);
        analogWrite(led1B, blueAltered);
      }
    }
  }
  if(presetFlash == 1){
    if(presetFlag == 0){
      int h = 0;
      while(h < 5){
        whiteOn();
        delay(30);
        off();
        delay(30);
        h = h++;
      }
      presetFlag = 1;
    }
    microsTimeThresh = 400;
    analogWrite(led1R, ledBrightness);
    analogWrite(led1G, ledBrightness);
    analogWrite(led1B, 255);
  }
  if(presetFlash == 2){
    if(presetFlag == 0){
      int h = 0;
      while(h < 5){
        whiteOn();
        delay(30);
        off();
        delay(30);
        h = h++;
      }
      presetFlag = 1;
    }
    microsTimeThresh = 400;
    analogWrite(led1R, 255);
    analogWrite(led1G, ledBrightness);
    analogWrite(led1B, 255);
  }
  if(presetFlash == 3){
    if(presetFlag == 0){
      int h = 0;
      while(h < 5){
        whiteOn();
        delay(30);
        off();
        delay(30);
        h = h++;
      }
      presetFlag = 1;
    }
    microsTimeThresh = 400;
    analogWrite(led1R, 255);
    analogWrite(led1G, 255);
    analogWrite(led1B, ledBrightness);
  }
}



