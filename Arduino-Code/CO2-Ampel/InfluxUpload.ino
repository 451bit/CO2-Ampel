void initFlux() {
  // Gerät hinzufügen
  sensor.addTag("device", SensorNameConfig);

  // NTP-Zeitsync
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Verdinbund überprüfen
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}

void uploadFlux() {
  // Felder des Messpunktes entfernen
  sensor.clearFields();

  // Neuen Messpunkt erstellen
  if (CO2Status) {
    sensor.addField("CO2", CO2ppm);
  }
  if (TempStatus) {
    sensor.addField("Temp", Temp);
  }
  if (HumidStatus) {
    sensor.addField("Humid", Humid);
  }

  // Messpunkt schreiben
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }
}
