void uploadServer() {
  // Sinnvolle Werte der Sensoren?
  String CO2ppmOk;
  String TempOk;
  String HumidOk;

  if (CO2Status) {
    CO2ppmOk = String(CO2ppm);
  } else {
    CO2ppmOk = "";
  }
  if (TempStatus) {
    TempOk = String(Temp);
  } else {
    TempOk = "";
  }
  if (HumidStatus) {
    HumidOk = String(Humid);
  } else {
    HumidOk = "";
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
                             + "&location=" + sensorLocation + "&valueco2=" + CO2ppmOk
                             + "&valuetemp=" + TempOk + "&valuehumid=" + HumidOk + "";

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
