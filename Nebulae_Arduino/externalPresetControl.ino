void externalMidiPreset(){
  while(midiRecall > 0){
    switch (midiRecall){
    case 1:
      midiRecall = 1;
      editMode();
      if(presetToggleCCPass == 0){
        midiOUT(0xB0, utilityCC, 12);
        presetToggleCCPass = 1;
      }
      break;
    case 2:
      midiRecall = 2;
      editMode();
      if(presetToggleCCPass == 0){
        midiOUT(0xB0, utilityCC, 13);
        presetToggleCCPass = 1;
      }
      break;
    case 3:
      midiRecall = 3;
      editMode();
      if(presetToggleCCPass == 0){
        midiOUT(0xB0, utilityCC, 14);
        presetToggleCCPass = 1;
      }
      break;
    }  
  }
}


