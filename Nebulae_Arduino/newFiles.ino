void newFiles(){
  mux3();
  if((digitalRead(buttonThree)) == HIGH){ //Toggle button assign
    int k = 0;  //Strobe to exit
    int reload = 0;
    t = 30;
    off();
    int v = 1;
    int c = 255;
    while(c > 0){
      analogWrite(led1R, c);
      analogWrite(led1B, 255);
      analogWrite(led1G, 255);
      analogWrite(ledR, c);
      analogWrite(ledL, c);
      analogWrite(ledF, c);
      c = c--;
      delay(3);
    }
    while(v == 1){
      blueOn();
      analogWrite(ledR, 255);
      analogWrite(ledL, 255);
      analogWrite(ledF, 255);
      if((digitalRead(buttonThree) == LOW)){
        v = 0;
      }
    }
    midiOUT(0xB0, 23, 23);//new files in looping Mode
    analogWrite(ledL, 255);
    analogWrite(ledR, 255);
    analogWrite(ledF, 255);
    off();
    delay(1000);
    reload = 0;
    gpioStateChange = 0;
    nextNext = 0;
    EDITMODE = 0;
    editModeState = 0;
    passOne = 0;
    passTwo = 0;
    readPause = 0;
    reload = 0;
    flashHold = 0;
    newFilesFlag = 1;
  }
}







