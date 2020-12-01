void initBlynk() {
  // Konfiguriert Verbindung zu Blynk
  char empty[] = "";
  if (memcmp(BlynkServer, empty, 1)) {
    // Eigener Server
    Blynk.config(auth, BlynkServer, BlynkServerPort);
  } else {
    // Standard-Blynk-Server
    Blynk.config(auth);
  }
  // Versucht Verbindung zu Blynk aufzubauen
  Blynk.connect();
}

void BlynkRun(){
  Blynk.run();
}

void uploadBlynk() {
 
  if (!Blynk.connected()) {
    // Verbindung neu aufbauen
    Blynk.connect();
    delay(100);
  }
  else {
    // Hochladen der Daten zu Blynk bei sinnvollen Werten
    
    if (CO2Status) {
      Blynk.virtualWrite(V0, CO2ppm);
    }
    if (TempStatus) {
      Blynk.virtualWrite(V1, Temp);
    }
    if (HumidStatus) {
      Blynk.virtualWrite(V2, Humid);
    }
  }
}

// Kalibrieren auf V-Pin 10 (Blynk)
BLYNK_WRITE(V10) {
  byte cali = param.asInt();
  if (cali) {
    Serial2.write(cmdCal, 9);
    // Display leeren
    Heltec.display->clear();
    // Kalibrieren
    Heltec.display->setFont(ArialMT_Plain_24);
    Heltec.display->drawString(0, 0, "Kalibrieren");
    // Display aktualisieren
    Heltec.display->display();
    delay(3000);
  }
}

// Neustart auf V-Pin 11 (Blynk)
BLYNK_WRITE(V11) {
  byte reset = param.asInt();
  if (reset) {
    ESP.restart();
  }
}
