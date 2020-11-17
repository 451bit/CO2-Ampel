// Sensor auslesen: Dokumentation zum Read-Cmd und zur Berechnung auf der Herstellerwebsite
void readSensor() {
  // Serial-Buffer leeren
  while (Serial2.available())
  {
    int garbage = Serial2.read();
  }

  // Read-Cmd an Sensor senden
  Serial2.write(cmd, 9);

  // Pausiert und wartet bis TX buffer gesendet hat
  Serial2.flush();

  // Sensordaten empfangen
  int StartTime = millis();
  int Timer = 0;

  // Pausiert und wartet 5 Sekunden auf Antwort des Sensors
  while (!Serial2.available() && Timer < 5000)
  {
    Timer = millis() - StartTime;
    delay(100);
  }

  //Schreibt Sensordaten in Var response
  Serial2.readBytes(response, 9);

  // Berechnet CO2 und schreibt Wert in Variable CO2ppm
  int responseHigh = (int)response[2];
  int responseLow = (int)response[3];
  CO2ppm = (256 * responseHigh) + responseLow;
}
