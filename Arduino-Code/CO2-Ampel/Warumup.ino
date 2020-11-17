// Aufwärmphase für den CO2-Sensor
void warumup() {
  // LED-Lauf
  while (TimerWarmup > 0) {
    if (TimerWarmup % 3  == 0) {
      analogWrite(redPin, 255);   // Write current values to LED pins
      analogWrite(grnPin, 0);
      analogWrite(yelPin, 0);
    }
    if (TimerWarmup % 3  == 1) {
      analogWrite(redPin, 0);   // Write current values to LED pins
      analogWrite(grnPin, 0);
      analogWrite(yelPin, 255);
    }
    if (TimerWarmup % 3  == 2) {
      analogWrite(redPin, 0);   // Write current values to LED pins
      analogWrite(grnPin, 255);
      analogWrite(yelPin, 0);
    }

    TimerWarmup--;

    //Display in Aufwärmphase aktualisieren
    Heltec.display->clear();
    Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
    Heltec.display->setFont(ArialMT_Plain_10);
    if (!Blynk.connected()) {
      Heltec.display->drawString(0, 0, "No Wifi");
    } else {
      Heltec.display->drawString(0, 0, "Blynk via " + WiFi.SSID());
    }
    Heltec.display->setFont(ArialMT_Plain_16);
    Heltec.display->drawString(0, 15, "Warmup: " + String(TimerWarmup));
    Heltec.display->display();
    delay(1000);
  }
  refresh();
}
