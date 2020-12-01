void initOLED() {
  // Display initialisieren (Heltec.begin() macht noch einiges anderes, das spielt aber keine Rolle)
  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->flipScreenVertically();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_24);
}

void displayData() {
  // Display leeren
  Heltec.display->clear();

  // Verbindung zu Blynk?
  Heltec.display->setFont(ArialMT_Plain_10);
  if (Blynk.connected() == 0) {
    Heltec.display->drawString(0, 0, "No Connection");
  } else {
    Heltec.display->drawString(0, 0, "Blynk via " + WiFi.SSID());
  }

  // Messwerte anzeigen
  Heltec.display->setFont(ArialMT_Plain_16);
  if (CO2Status) {
    Heltec.display->drawString(0, 15, "CO2: " + String(CO2ppm) + " ppm");
  } else {
    Heltec.display->drawString(0, 15, "CO2-Error");
  }

  if (TempStatus) {
    Heltec.display->drawString(0, 30, "Temp: " + String(Temp) + " °C");
  } else {
    Heltec.display->drawString(0, 30, "Temp-Error");
  }

  if (HumidStatus) {
    Heltec.display->drawString(0, 45, "Humid.: " + String(Humid) + " %");
  } else {
    Heltec.display->drawString(0, 45, "Humid-Error");
  }

  // Display aktualisieren
  Heltec.display->display();
}
