void colourSweep(){
  off();
  //Red
  for(int i = 255; i >= 0; i -=fadeDivision){
    analogWrite(led1R, i);
    delay(time);
  }
  for(int i = 255; i >= 0; i -=fadeDivision){
    delay(time);
  }
  //Yellow
  for(int i = 255; i >= 0; i -=fadeDivision){
    analogWrite(led1G, i);
    delay(time);
  }
  for(int i = 255; i >= 0; i -=fadeDivision){
    delay(time);
  }
  //Green
  for(int i = 0; i <= 255; i +=fadeDivision){
    analogWrite(led1R, i);
    delay(time);
  }
  for(int i = 0; i <= 255; i +=fadeDivision){
    delay(time);
  }
  //cyan
  for(int i = 255; i >= 0; i -=fadeDivision){
    analogWrite(led1B, i);
    delay(time);
  }
  for(int i = 255; i >= 0; i -=fadeDivision){
    delay(time);
  }
  //Blue
  for(int i = 0; i <= 255; i +=fadeDivision){
    analogWrite(led1G, i);
    delay(time);
  }
  for(int i = 0; i <= 255; i +=fadeDivision){
    delay(time);
  }
  //Magenta
  for(int i = 255; i >= 0; i -=fadeDivision){
    analogWrite(led1R, i);
    delay(time);
  }
  for(int i = 255; i >= 0; i -=fadeDivision){
    delay(time);
  }
  //Red
  for(int i = 0; i <= 255; i +=fadeDivision){
    analogWrite(led1B, i);
    delay(time);
  }
  for(int i = 0; i <= 255; i +=fadeDivision){
    delay(time);
  }
  analogWrite(led1R, 255);
  analogWrite(led1G, 255);
  analogWrite(led1B, 255);
}

void redOn(){
  analogWrite(led1R, 0);
  analogWrite(led1G, 255);
  analogWrite(led1B, 255);
}
void yellowOn(){
  analogWrite(led1R, 0);
  analogWrite(led1G, 0);
  analogWrite(led1B, 255);
}
void greenOn(){
  analogWrite(led1R, 255);
  analogWrite(led1G, 0);
  analogWrite(led1B, 255);
}
void cyanOn(){
  analogWrite(led1R, 255);
  analogWrite(led1G, 0);
  analogWrite(led1B, 0);
}
void blueOn(){
  analogWrite(led1R, 255);
  analogWrite(led1G, 255);
  analogWrite(led1B, 0);
}
void magentaOn(){
  analogWrite(led1R, 0);
  analogWrite(led1G, 255);
  analogWrite(led1B, 0);
}
void whiteOn(){
  analogWrite(led1R, 0);
  analogWrite(led1G, 0);
  analogWrite(led1B, 0);
}
void off(){
  analogWrite(led1R, 255);
  analogWrite(led1G, 255);
  analogWrite(led1B, 255);
}

void Forward(){
  fader2Millis = millis();
  if(ledStep == 1){
    lightBright = 0;
    analogWrite(ledL, 0);
    analogWrite(ledR, 255);
    ledStep = 2;
  }
  if((ledStep == 2) && ((fader2Millis - fader2MillisPre) > 1)){
    fader2MillisPre = fader2Millis;
    lightBright = lightBright++;
    if(lightBright > 254){
      lightBright = 255;
      ledStep = 3;
    }
    analogWrite(ledL, lightBright);
    analogWrite(ledR, 255);
  }
  if((ledStep == 3) && ((fader2Millis - fader2MillisPre) > 10)){ //fadeBreak
    fader2MillisPre = fader2Millis;
    ledStep = 4;
  }
  if((ledStep == 4) && ((fader2Millis - fader2MillisPre) > 1)){
    fader2MillisPre = fader2Millis;
    lightBright = lightBright--;
    if(lightBright < 1){
      lightBright = 0;
      ledStep = 5;
    }
    analogWrite(ledR, lightBright);
    analogWrite(ledL, 255);
  }
  if((ledStep == 5) && ((fader2Millis - fader2MillisPre) > 100)){
    fader2MillisPre = fader2Millis;
    analogWrite(ledR, 255);
    analogWrite(ledL, 255);
    ledStep = 6;
  }
  if((ledStep == 6) && ((fader2Millis - fader2MillisPre) > 400)){
    fader2MillisPre = fader2Millis;
    ledStep = 1;
  }
}

void Backward(){
  fader2Millis = millis();
  if(ledStep == 1){
    lightBright = 0;
    analogWrite(ledR, 0);
    analogWrite(ledL, 255);
    ledStep = 2;
  }
  if((ledStep == 2) && ((fader2Millis - fader2MillisPre) > 1)){
    fader2MillisPre = fader2Millis;
    lightBright = lightBright++;
    if(lightBright > 254){
      lightBright = 255;
      ledStep = 3;
    }
    analogWrite(ledR, lightBright);
    analogWrite(ledL, 255);
  }
  if((ledStep == 3) && ((fader2Millis - fader2MillisPre) > 10)){ //fadeBreak
    fader2MillisPre = fader2Millis;
    ledStep = 4;
  }
  if((ledStep == 4) && ((fader2Millis - fader2MillisPre) > 1)){
    fader2MillisPre = fader2Millis;
    lightBright = lightBright--;
    if(lightBright < 1){
      lightBright = 0;
      ledStep = 5;
    }
    analogWrite(ledL, lightBright);
    analogWrite(ledR, 255);
  }
  if((ledStep == 5) && ((fader2Millis - fader2MillisPre) > 100)){
    fader2MillisPre = fader2Millis;
    analogWrite(ledL, 255);
    analogWrite(ledR, 255);
    ledStep = 6;
  }
  if((ledStep == 6) && ((fader2Millis - fader2MillisPre) > 400)){
    fader2MillisPre = fader2Millis;
    ledStep = 1;
  }
}

void Random(){
  fader2Millis = millis();
  if((fader2Millis - fader2MillisPre1) > randAlt1){
    randAlt1 = random(30, 250);
    ledChange1 = ledChange1++;
    if(ledChange1 > 1){
      ledChange1 = 0;
    }
    fader2MillisPre1 = fader2Millis;
  }
  if(ledChange1 == 1){
    analogWrite(ledL, 0);
  }
  if(ledChange1 == 0){
    analogWrite(ledL, 255);
  }
  if((fader2Millis - fader2MillisPre2) > randAlt2){
    randAlt2 = random(30, 250);
    ledChange2 = ledChange2++;
    if(ledChange2 > 1){
      ledChange2 = 0;
    }
    fader2MillisPre2 = fader2Millis;
  }
  if(ledChange2 == 1){
    analogWrite(ledR, 0);
  }
  if(ledChange2 == 0){
    analogWrite(ledR, 255);
  }
}

void bootUp(){
  bootUpMillis = micros();
  if((bootUpMillis - bootUpMillisPre) > 300){
    if(ledBrightness > 254){
      off();
    }
    if(ledBrightness > 400){
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
  ledBrightConstrain = constrain(ledBrightness, 0, 255);
  if(nextNext == 0){
    analogWrite(led1R, ledBrightConstrain);
    analogWrite(led1G, 255);
    analogWrite(led1B, 255);
  }
  if(nextNext == 1){
    analogWrite(led1R, ledBrightConstrain);
    analogWrite(led1G, ledBrightConstrain);
    analogWrite(led1B, ledBrightConstrain);
  }
  if(nextNext == 2){
    fader2Millis = millis();
    if((fader2Millis - fader2MillisPre1) > randAlt1){
      randAlt1 = random(30, 250);
      ledChange1 = ledChange1++;
      if(ledChange1 > 1){
        ledChange1 = 0;
      }
      fader2MillisPre1 = fader2Millis;
    }
    if(ledChange1 == 1){
      analogWrite(led1R, 0);
      analogWrite(led1G, 255);
      analogWrite(led1B, 255);
    }
    if(ledChange1 == 0){
      analogWrite(led1R, ledBrightConstrain);
      analogWrite(led1G, ledBrightConstrain);
      analogWrite(led1B, ledBrightConstrain);
    }
  }
}
