void uploadServer() {
  // Sinnvolle Werte der Sensoren?
  int CO2ppmOk;
  int TempOk;
  int HumidOk;

  if (CO2ppm > 300 && CO2ppm < 4999) {
    CO2ppmOk = CO2ppm;
  } else {
    CO2ppmOk = 0;
  }
  if (Temp > -10 && Temp < 99) {
    TempOk = Temp;
  } else {
    TempOk = 0;
  }
  if (Humid > 1 && Humid < 100) {
    HumidOk = Humid;
  } else {
    HumidOk = 0;
  }

  // Hochladen der Daten auf eigenen Server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Servername/URL
    http.begin(serverName);

    // Header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // HTTP POST-Daten erzeugen
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                             + "&location=" + sensorLocation + "&valueco2=" + String(CO2ppmOk)
                             + "&valuetemp=" + String(TempOk) + "&valuehumid=" + String(HumidOk) + "";

    // HTTP POST-Daten senden
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      //Serial.print("HTTP Response code: ");
      //Serial.println(httpResponseCode);
    }
    else {
      //Serial.print("Error code: ");
      //Serial.println(httpResponseCode);
    }
    // Ende
    http.end();
  }
  else {
   // Serial.println("WiFi Disconnected");
  }
}
