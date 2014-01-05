//////////////////////////////////////////////////////////////////////
//==================================================================//
//============================ MIDI ================================//
//==================================================================//
//////////////////////////////////////////////////////////////////////
void midiOUT(char command, char value1, char value2) {
  if(nextNext > 3){
    if(midiMute == 0){
      Serial.write(command);
      Serial.write(value1);
      Serial.write(value2);
    }
  }
}
//======================== Mux Controls ============================//
//Note:  Multiplexer 1 reads on A0
//       Multiplexer 2 reads on A1
void mux0(){
  digitalWrite(S0, LOW);    
  digitalWrite(S1, LOW);    
  digitalWrite(S2, LOW);    
}
void mux1(){
  digitalWrite(S0, HIGH);    
  digitalWrite(S1, LOW);     
  digitalWrite(S2, LOW);     
}
void mux2(){
  digitalWrite(S0, LOW);     
  digitalWrite(S1, HIGH);    
  digitalWrite(S2, LOW);     
}
void mux3(){
  digitalWrite(S0, HIGH);    
  digitalWrite(S1, HIGH);    
  digitalWrite(S2, LOW);     
}
void mux4(){
  digitalWrite(S0, LOW);     
  digitalWrite(S1, LOW);     
  digitalWrite(S2, HIGH);    
}
void mux5(){
  digitalWrite(S0, HIGH);     
  digitalWrite(S1, LOW);    
  digitalWrite(S2, HIGH);    
}
void mux6(){
  digitalWrite(S0, LOW);     
  digitalWrite(S1, HIGH);    
  digitalWrite(S2, HIGH);    
}
void mux7(){
  digitalWrite(S0, HIGH);    
  digitalWrite(S1, HIGH);    
  digitalWrite(S2, HIGH);    
}

