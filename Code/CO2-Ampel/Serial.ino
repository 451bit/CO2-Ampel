void initSerial(int Ser2RX, int Ser2TX) {
  // Serial2 zur Komm. mit Sensor auf den Pins Ser2RX und Ser2TX initialisieren
  Serial2.begin(9600, SERIAL_8N1, Ser2RX, Ser2TX);
}

void writeDataSerial() {
  // Daten ausgeben
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println("----------------------------------------------------------------------------------------------------");
  Serial.println("Wifi Connection");
  if (WiFi.isConnected()) {
    Serial.println("Wifi: " + WiFi.SSID());
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("No Wifi");
  }

  if (Blynk.connected()) {
    Serial.println("Blynk connected to Server " + String(BlynkServer) + " with Token " + String(auth));
  } else {
    Serial.println("Not connected to Blynk");
  }

  Serial.println();
  Serial.println("Data");
  Serial.println("CO2: " + String(CO2ppm) + " ppm");
  Serial.println("Temp: " + String(Temp) + " °C");
  Serial.println("Feuchtigkeit: " + String(Humid) + " %");
  Serial.println("----------------------------------------------------------------------------------------------------");
}
