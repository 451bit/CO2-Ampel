void initOTA() {
  // Zur Drahtlos-Komm. mit dem ESP im Wlan
  ArduinoOTA.setHostname("ESP-CO2 Monitor");  
  ArduinoOTA.begin();  
}
