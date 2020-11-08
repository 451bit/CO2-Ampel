void initLED() {
  // LEDs initialisieren
  pinMode(redPin, OUTPUT);   // sets the pins as output
  pinMode(grnPin, OUTPUT);
  pinMode(yelPin, OUTPUT);
}

void LEDStatus() {
  // CO2 unbedenklich -> grün
  if (CO2ppm < 700 && CO2ppm >= 200) {
    analogWrite(redPin, 0);   
    analogWrite(grnPin, 255);
    analogWrite(yelPin, 0);
  }

  // CO2 zu hoch -> rot
  if (CO2ppm > 1200 && CO2ppm < 4999) {
    analogWrite(redPin, 255);  
    analogWrite(grnPin, 0);
    analogWrite(yelPin, 0);    
  }

  // CO2 noch ok -> gelb
  if (CO2ppm <= 1200 && CO2ppm >= 700) {
    analogWrite(redPin, 0);   
    analogWrite(grnPin, 0);
    analogWrite(yelPin, 255);
  }

  // CO2-Fehler (vermutlich sinnlose Werte)
  if (CO2ppm < 200 || CO2ppm >= 4999) {
    for (int i = 0; i < 10; i++) {
      analogWrite(redPin, 255);   
      analogWrite(grnPin, 255);
      analogWrite(yelPin, 255);
      delay(100);
      analogWrite(redPin, 0);   
      analogWrite(grnPin, 0);
      analogWrite(yelPin, 0);
      delay(100);
    }
  }
}
