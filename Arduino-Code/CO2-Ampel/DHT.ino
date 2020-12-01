void initDHT() {
  // Temp-Sensor init
  dht.begin();
}

void readDHT() {
  //Temp und Humid auslesen und in Var schreiben
  int TempRaw = dht.readTemperature();
  int HumidRaw = dht.readHumidity();
  if (Humid >= 0 && Humid <= 100) {
    Humid = HumidRaw;
    HumidStatus = true;    
  } else {
    Humid = 0;
    HumidStatus = false;
  }
  if (Temp >= -40 && Temp <= 80) {
    Temp = TempRaw;
    TempStatus = true;    
  } else {
    Temp = 0;
    TempStatus = false;
  }
}
