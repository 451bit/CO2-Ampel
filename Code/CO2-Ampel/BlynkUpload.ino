void initWifiBlynk() {
  delay(10);
  memset(ssid_char, 0, 50);
  memset(pw_char, 0, 50);
  SSID_1.toCharArray(ssid_char, 50);
  WIFI_PW_1.toCharArray(pw_char, 50);
  wifiMulti.addAP(ssid_char, pw_char);

  memset(ssid_char, 0, 50);
  memset(pw_char, 0, 50);
  SSID_2.toCharArray(ssid_char, 50);
  WIFI_PW_2.toCharArray(pw_char, 50);
  wifiMulti.addAP(ssid_char, pw_char);

  memset(ssid_char, 0, 50);
  memset(pw_char, 0, 50);
  SSID_3.toCharArray(ssid_char, 50);
  WIFI_PW_3.toCharArray(pw_char, 50);
  wifiMulti.addAP(ssid_char, pw_char);

  // Timer für den Check der Wifi-Verbindung starten. 1. Parameter: Timer-Zeit (in ms), 2. Parameter: Methode, die ausgeführt wird
  TimerWifi.setInterval(TimerWifiInterval * 1000, CheckConnection);
  MyWiFi();
}

// Baut Wifi- und Blynk-Verbindung auf
void MyWiFi() {
  // Netzwerk verbinden
  if (wifiMulti.run() == WL_CONNECTED) {
    MYSSID = WiFi.SSID();
    initOTA();
  }

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

// Prüft ob Verbindung zu Blynk
void CheckConnection() {
  if (!Blynk.connected()) {
    // Verbindung neu aufbauen
    MyWiFi();
  }
  else {
    // Hochladen der Daten zu Blynk bei sinnvollen Werten
    Blynk.run();
    if (CO2ppm > 300 && CO2ppm < 4999) {
      Blynk.virtualWrite(V0, CO2ppm);
    }
    if (Temp > -10 && Temp < 99) {
      Blynk.virtualWrite(V1, Temp);
    }
    if (Humid > 1 && Humid < 100) {
      Blynk.virtualWrite(V2, Humid);
    }
  }
}

// Kalibrieren auf V-Pin 10 (Blynk)
BLYNK_WRITE(V10) {
  byte cali = param.asInt();
  if (cali) {
    Serial2.write(cmdCal, 9);
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
