void HandleNoteOn(byte channel, byte pitch, byte velocity) { 
  if(modeMidiNotes == 0){//Looping Mode
    iPitch = 0;
    if(velocity > 0){
      iMIDIMap = 1;
    }
    pitchMap = pitch;
    pitchMap = map(pitchMap, 36, 96, 0, 1023);
  }
  if(modeMidiNotes == 1){//OneShot Mode
    if(pitch == 60){
      if(velocity > 0){
        midiOUT(0xB0, 1, 127);
        redOn();
        delay(30);
        off();
        midiOUT(0xB0, 1, 0);
      }
    }
    if(pitch == 62){
      if(velocity > 0){
        midiOUT(0xB0, 2, 127);
        analogWrite(led1R, 0);
        analogWrite(led1G, 210);
        analogWrite(led1B, 255);
        delay(30);
        off();
        midiOUT(0xB0, 2, 0);
      }
    }
    if(pitch == 64){
      if(velocity > 0){
        midiOUT(0xB0, 3, 127);
        yellowOn();
        delay(30);
        off();
        midiOUT(0xB0, 3, 0);
      }
    }
    if(pitch == 65){
      if(velocity > 0){
        midiOUT(0xB0, 4, 127);
        greenOn();
        delay(30);
        off();
        midiOUT(0xB0, 4, 0);
      }
    }
    if(pitch == 67){
      if(velocity > 0){
        midiOUT(0xB0, 5, 127);
        cyanOn();
        delay(30);
        off();
        midiOUT(0xB0, 5, 0);
      }
    }
    if(pitch == 69){
      if(velocity > 0){
        midiOUT(0xB0, 6, 127);
        blueOn();
        delay(30);
        off();
        midiOUT(0xB0, 6, 0);
      }
    }
    if(pitch == 71){
      if(velocity > 0){
        midiOUT(0xB0, 7, 127);
        magentaOn();
        delay(30);
        off();
        midiOUT(0xB0, 7, 0);
      }
    }
    if(pitch == 72){
      if(velocity > 0){
        midiOUT(0xB0, 8, 127);
        whiteOn();
        delay(30);
        off();
        midiOUT(0xB0, 8, 0);
      }
    }
    //============== Sample Off messages ==============//
    if(pitch == 74){//Kill all
      if(velocity > 0){
        midiOUT(0xB0, 28, 127);
        whiteOn();
        delay(30);
        off();
        midiOUT(0xB0, 28, 0);
      }
    }
    if(pitch == 84){
      if(velocity > 0){
        midiOUT(0xB0, 1, 63);
        redOn();
        delay(30);
        off();
        midiOUT(0xB0, 1, 0);
      }
    }
    if(pitch == 86){
      if(velocity > 0){
        midiOUT(0xB0, 2, 63);
        analogWrite(led1R, 0);
        analogWrite(led1G, 210);
        analogWrite(led1B, 255);
        delay(30);
        off();
        midiOUT(0xB0, 2, 0);
      }
    }
    if(pitch == 88){
      if(velocity > 0){
        midiOUT(0xB0, 3, 63);
        yellowOn();
        delay(30);
        off();
        midiOUT(0xB0, 3, 0);
      }
    }

    if(pitch == 89){
      if(velocity > 0){
        midiOUT(0xB0, 4, 63);
        greenOn();
        delay(30);
        off();
        midiOUT(0xB0, 4, 0);
      }
    }
    if(pitch == 91){
      if(velocity > 0){
        midiOUT(0xB0, 5, 63);
        cyanOn();
        delay(30);
        off();
        midiOUT(0xB0, 5, 0);
      }
    }
    if(pitch == 93){
      if(velocity > 0){
        midiOUT(0xB0, 6, 63);
        blueOn();
        delay(30);
        off();
        midiOUT(0xB0, 6, 0);
      }
    }
    if(pitch == 95){
      if(velocity > 0){
        midiOUT(0xB0, 7, 63);
        magentaOn();
        delay(30);
        off();
        midiOUT(0xB0, 7, 0);
      }
    }
    if(pitch == 96){
      if(velocity > 0){
        midiOUT(0xB0, 8, 63);
        whiteOn();
        delay(30);
        off();
        midiOUT(0xB0, 8, 0);
      }
    }
  }
}

void HandlePitchBend (byte channel, int bend){
  if((bend > 0) || (bend < 0)){
    bendGate = 1;
    bendMap = map(bend, -8192, 8191, -34, 34);
  }
  if(bend == 0){
    bendGate = 0;
  }
}

void HandleControlChange(byte channel, byte number, byte value){ 
  if(globalOperation == 0){//Looping
    //|||||||| Freeze ||||||||||
    if((number == 20) && (EDITMODE == 0)){
      if(value == 127){
        freezeButtonToggle = freezeButtonToggle++; 
        if(freezeButtonToggle > 1){
          freezeButtonToggle = 0;
        }
      }
    }
    //|||||||| Next ||||||||||
    if(number == 21){
      if(value == 127){
        whiteOn();
        midiOUT(0xB0, utilityCC, 3);
        delay(80);
        midiOUT(0xB0, utilityCC, 4);
        off();
      }
    }
    //|||||||| Porta/Glide ||||||||||
    if(number == 5){
      iPortamento = 30;
      midiOUT(0xB0, 70, value);
    }
    //|||||||| Speed (MSB) ||||||||||
    if(number == 12){
      iSpeed = 30;
      midiOUT(0xB0, 1, value);
    }
    //|||||||| Speed (LSB) ||||||||||
    if(number == 44){
      midiOUT(0xB0, 2, value);
    }
    //|||||||| Pitch (MSB) ||||||||||  
    if(number == 13){
      iPitch = 30;
      midiOUT(0xB0, 15, value);
    }
    //|||||||| Pitch (MSB) ||||||||||
    if(number == 45){
      midiOUT(0xB0, 16, value);
    }

    //|||||||| Loop Start (MSB) ||||||||||
    if(number == 14){
      iStart = 30;
      midiOUT(0xB0, 9, value);
    }
    //|||||||| Loop Start (LSB) ||||||||||
    if(number == 46){
      midiOUT(0xB0, 10, value);
    }
    //|||||||| Loop Size (MSB) ||||||||||
    if(number == 15){
      iEnd = 30;
      midiOUT(0xB0, 11, value);
    }
    //|||||||| Loop Size (LSB) ||||||||||
    if(number == 47){
      midiOUT(0xB0, 12, value);
    }
    //|||||||| Mix ||||||||||
    if(number == 16){
      iMix = 30;
      midiOUT(0xB0, 8, value);
    }
    //|||||||| Grain Size ||||||||||
    if(number == 17){
      igSize = 30;
      midiOUT(0xB0, 4, value);
    }
    //|||||||| Grain Rate ||||||||||
    if(number == 18){
      igRate = 30;
      midiOUT(0xB0, 5, value);
    }
    //|||||||| Preset Recall ||||||||||
    if(number == 25){
      if((value == 127) && (midiRecall == 0)){
        midiRecall = 1;
      }
      if(value < 127){
        midiRecall = 0;
      }
    }
    if((number == 26) && (midiRecall == 0)){
      if(value == 127){
        midiRecall = 2;
      }
      if(value < 127){
        midiRecall = 0;
      }
    }
    if((number == 27) && (midiRecall == 0)){
      if(value == 127){
        midiRecall = 3;
      }
      if(value < 127){
        midiRecall = 0;
      }
    }
    //|||||||| Preset save ||||||||||
    if(number == 22){
      if(value == 127){
        off();
        int k = 0;
        while(k < 10){
          off();
          yellowOn();
          delay(25);
          off();
          delay(25);
          k = k++;
        }
        midiOUT(0xB0, utilityCC, 18);//Write to preset
        delay(40);
        midiOUT(0xB0, utilityCC, 22);
      } 
    }
    if(number == 23){
      if(value == 127){
        off();
        int k = 0;
        while(k < 10){
          off();
          greenOn();
          delay(25);
          off();
          delay(25);
          k = k++;
        }
        midiOUT(0xB0, utilityCC, 19);//Write to preset
        delay(40);
        midiOUT(0xB0, utilityCC, 22);
      } 
    }
    if(number == 24){
      if(value == 127){
        off();
        int k = 0;
        while(k < 10){
          off();
          blueOn();
          delay(25);
          off();
          delay(25);
          k = k++;
        }
        midiOUT(0xB0, utilityCC, 20);//Write to preset
        delay(40);
        midiOUT(0xB0, utilityCC, 22);
      } 
    }
  }
  if(globalOperation == 1){//OneShot
    //smp1MSB
    if(number == 1){
      dontIgnore = 1;
      iSpeed = 30;
      midiOUT(0xB0, 9, value);
    }
    //smp1LSB
    if(number == 32){
      midiOUT(0xB0, 10, value);
    }
    //smp2MSB
    if(number == 2){
      dontIgnore = 1;
      iPortamento = 30;
      midiOUT(0xB0, 11, value);
    }
    //smp2LSB
    if(number == 33){
      midiOUT(0xB0, 12, value);
    }
    //smp3MSB
    if(number == 3){
      dontIgnore = 1;
      iPitch = 30;
      midiOUT(0xB0, 13, value);
    }
    //smp3LSB
    if(number == 34){
      midiOUT(0xB0, 14, value);
    }
    //smp4MSB
    if(number == 4){
      dontIgnore = 1;
      iMix = 30;
      midiOUT(0xB0, 15, value);
    }
    //smp4LSB
    if(number == 35){
      midiOUT(0xB0, 16, value);
    }

    //smp5MSB
    if(number == 5){
      dontIgnore = 1;
      igSize = 30;
      midiOUT(0xB0, 17, value);
    }
    //smp5LSB
    if(number == 36){
      midiOUT(0xB0, 18, value);
    }
    //smp6MSB
    if(number == 6){
      dontIgnore = 1;
      igRate = 30;
      midiOUT(0xB0, 19, value);
    }
    //smp6LSB
    if(number == 37){
      midiOUT(0xB0, 20, value);
    }
    //smp7MSB
    if(number == 7){
      dontIgnore = 1;
      iStart = 30;
      midiOUT(0xB0, 21, value);
    }
    //smp7LSB
    if(number == 38){
      midiOUT(0xB0, 22, value);
    }
    //smp8MSB
    if(number == 8){
      dontIgnore = 1;
      iEnd = 30;
      midiOUT(0xB0, 24, value);
    }
    //smp8LSB
    if(number == 39){
      midiOUT(0xB0, 25, value);
    }
  }
}













