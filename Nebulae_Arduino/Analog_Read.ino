void readAllAnalog(){
  //Mux
  mux0();
  freezeRaw = analogRead(A0);
  startCVRaw = analogRead(A1);
  //
  mux1();
  presetToggleCVRaw = analogRead(A0);
  startPotRaw = analogRead(A1);
  //
  mux2();
  pitchPotRaw = analogRead(A0);
  endPotRaw = analogRead(A1);
  //
  mux3();
  nextRaw = analogRead(A0);
  //
  mux4();
  mixCVRaw = analogRead(A0);
  gRatePotRaw = analogRead(A1);
  //
  mux5();
  gSizePotRaw = analogRead(A0);
  gSizeCVRaw = analogRead(A1);
  //
  mux6();
  speedCVRaw = analogRead(A0);
  gRateCVRaw = analogRead(A1);
  //
  mux7();
  mixPotRaw = analogRead(A0);
  endCVRaw = analogRead(A1);
  //
  portamentoPotRaw = analogRead(A3); 
  speedPotRaw = analogRead(A5);  
  pitchCVRaw = analogRead(A4); 
}

