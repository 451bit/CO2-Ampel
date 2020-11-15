void initWifi() {
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
  myWiFi();
}

// Baut Wifi- und Blynk-Verbindung auf
void myWiFi() {
  // Netzwerk verbinden
  if (wifiMulti.run() == WL_CONNECTED) {
    MYSSID = WiFi.SSID();
    initOTA();
  }
}

// Prüft ob Verbindung zu Blynk und Internet
void checkConnection() {
  if (!wifiMulti.run() == WL_CONNECTED) {
    myWiFi();
  }  
}
