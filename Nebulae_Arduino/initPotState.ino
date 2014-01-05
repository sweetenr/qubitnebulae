void initPotState(){
  //STARTUP POT POSITIONS
  delay(20);
  midiOUT(0xB0, 23, 0);
  int SPMSB = (speedPotRaw >> 3) & 0x7F; 
  int SPLSB = (speedPotRaw & 0x7) << 4;
  midiOUT(0xB0, 1, SPMSB);
  midiOUT(0xB0, 2, SPLSB);
  delay(20);
  int PTMSB = (pitchPotRaw >> 3) & 0x7F;
  int PTLSB = (pitchPotRaw & 0x7) << 4;
  midiOUT(0xB0, 15, PTMSB);
  midiOUT(0xB0, 16, PTLSB);
  delay(20);
  int ENDMSB = (endPotRaw >> 3) & 0x7F;
  int ENDLSB = (endPotRaw & 0x7) << 4;
  midiOUT(0xB0, 11, ENDMSB);
  midiOUT(0xB0, 12, ENDLSB);
  delay(20);
  int STMSB = (startPotRaw >> 3) & 0x7F;
  int STLSB = (startPotRaw & 0x7) << 4;
  midiOUT(0xB0, 9, STMSB);
  midiOUT(0xB0, 10, STLSB);
  delay(20);
  midiOUT(0xB0, 4, gSizePotRaw/8);
  midiOUT(0xB0, 5, gRatePotRaw/8);
  midiOUT(0xB0, 8, mixPotRaw/8);
  midiOUT(0xB0, 70, portamentoPotRaw/8);
}
