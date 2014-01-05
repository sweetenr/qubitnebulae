void gpioRead(){
  //mux4();
  //Smoothing
  /*
  Adapted from Arduino Smoothing example
  originally created 22 April 2007
  By David A. Mellis  <dam@mellis.org>
  modified 9 Apr 2012
  by Tom Igoe
  http://www.arduino.cc/en/Tutorial/Smoothing
  */
  gpioRaw = analogRead(A2);
  startTotal = startTotal - startReadings[startIndex];
  startReadings[startIndex] = gpioRaw;
  startTotal = startTotal + startReadings[startIndex];
  startIndex = startIndex + 1;
  if(startIndex >= numStartReadings)
    startIndex = 0;
  startAverage = startTotal/numStartReadings;
  if(startAverage > 600){
    gpio = 1;
  }
  else if(startAverage <= 600){
    gpio = 0;
  }
  if((gpio == 1) && (gpioTog == 0)){
    gpioStateChange = gpioStateChange++;
    gpioTog = 1;
  }
  if((gpio == 0) && (gpioTog == 1)){
    gpioStateChange = gpioStateChange++;
    gpioTog = 0;
  }
  if((gpioStateChange == 1) && (nextNext == 0)){
    nextNext = 1;
  }
  if((gpioStateChange == 2) && (nextNext == 1)){
    nextNext = 2;
  }
  if((gpioStateChange == 3) && (nextNext == 2)){
    nextNext = 3;
  }
}
