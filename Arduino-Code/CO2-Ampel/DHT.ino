void initDHT() {
  // Temp-Sensor init
  dht.begin();
}

void readDHT() {
  //Temp und Humid auslesen und in Var schreiben
  Temp = dht.readTemperature();
  Humid = dht.readHumidity();
}
