void presetToggleCVolt(){
  presetToggleCV = presetToggleCVRaw/512;
  if(abs(presetToggleCV - presetToggleCVPre) >= 1){
    presetToggleCVVal = presetToggleCV;
    presetToggleCVPre = presetToggleCV;
  }
  if((presetToggleCVVal == 1) && (presetToggleCVState == 1)){//Preset Hold
    off();
    delay(6);
    presetHold = 1;  
    hideLights = 1;
    mux1();   
    while((analogRead(A0)/512) == 1){
      switch (presetToggle){
      case 1:
        if(presetToggleCCPass == 0){
          presetFlash = 1;
          midiOUT(0xB0, utilityCC, 12);
          presetToggleCCPass = 1;
        }
        editMode();
        break;
      case 2:
        if(presetToggleCCPass == 0){
          presetFlash = 2;
          midiOUT(0xB0, utilityCC, 13);
          presetToggleCCPass = 1;
        }
        editMode();
        break;
      case 3:
        if(presetToggleCCPass == 0){
          presetFlash = 3;
          midiOUT(0xB0, utilityCC, 14);
          presetToggleCCPass = 1;
        }
        editMode();
        break;
      }
    }
    hideLights = 0;
    presetToggleCVState = 0;
  }
  if((presetToggleCVVal == LOW) && (presetToggleCVState == 0)){
    presetToggleCCPass = 0;
    midiOUT(0xB0, utilityCC, 16);
    off();
    presetToggleCVState = 1;   
  }
}

