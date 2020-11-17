#include <Arduino.h>
#include "Configuration.h"
#include "heltec.h"
#include <WiFiMulti.h>
#include <BlynkSimpleEsp32_SSL.h>
#include <ArduinoOTA.h>
#include <analogWrite.h>
#include "DHT.h"
// Temp-Sensor Typ
#define DHTTYPE DHT22
#include <HTTPClient.h>

// Blynk Daten
// BlynkServer leer lassen, falls der Standard-Blynk-Server verwendet werden soll. Ansonsten die URL und Port des eigenen Servers eintragen
// Wenn auf dem eigenen Server ein LetsEncrypt-Zertifikat verwendet wird, dann Zeile 2 "#define BLYNK_SSL_USE_LETSENCRYPT" aktivieren
char BlynkServer[] = BlynkServerConfig;
uint16_t BlynkServerPort = BlynkServerPortConfig;
char auth[] = BlynkAuthConfig;

// Server Daten für den Upload auf einen eigenen Server (zur Darstellung auf Homepage)
String sensorName = SensorNameConfig;
String sensorLocation = SensorLocationConfig;
String apiKeyValue = ApiKeyValueConfig;
const char* serverName = ServerNameConfig;

// HIER DIE WIFI-DATEN EINGEBEN
String SSID_1 = SSID1Config;
String WIFI_PW_1 = WiFiPwConfig1;
String SSID_2 = SSID2Config;
String WIFI_PW_2 = WiFiPwConfig2;
String SSID_3 = SSID3Config;
String WIFI_PW_3 = WiFiPwConfig3;

//Pin-Belegung
int Ser2TX = 23;  // Serial 2 TX Pin to CO2-Sensor RX
int Ser2RX = 22;  // Serial 2 RX Pin to CO2-Sensor TX
int grnPin = 19;  // Pins der LEDs
int yelPin = 18;
int redPin = 17;
#define DHTPIN 5
DHT dht(DHTPIN, DHTTYPE);

//Sensorwerte
int CO2ppm = 0;
int Temp = 0;
int Humid = 0;

// Kommandos zum Lesen und Kalibrieren des Sensors
byte cmd[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};  // Lesebefehl
byte cmdCal[9] = {0xFF, 0x01, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78};  // Kalibrier-Befehl
char response[9];  // Antwort des Sensors

// Timer
int TimerWarmup = 60; // Warumup-Timer
SimpleTimer TimerRefresh; // Timer zum Aktualisieren der Daten
int TimerRefreshInterval = 10;
SimpleTimer TimerWifi; // Timer zur Prüfung der Netzwerkverbindung
int TimerWifiInterval = 1;
SimpleTimer TimerUpload; // Timer zum Upload der Daten
int TimerUploadInterval = 30;

// Wifi-Daten. Hier muss nichts eingetragen werden
WiFiMulti wifiMulti;
String MYSSID = "";
char ssid_char[50];
char pw_char[50];

// Initialisierung und Timer zum Aktualisieren der Sensordaten Starten
void setup() {
  initSerial(Ser2RX, Ser2TX);
  initOLED();
  initLED();
  initDHT();
  initWifi();
  initBlynk();
  warumup();
  TimerRefresh.setInterval(TimerRefreshInterval * 1000, refresh);
  TimerWifi.setInterval(TimerWifiInterval * 1000, ConnectWifi);
  TimerUpload.setInterval(TimerUploadInterval * 1000, upload);
}

// OTA und Timer abfragen
void loop() {
  ArduinoOTA.handle();
  TimerRefresh.run();
  TimerWifi.run();
  TimerUpload.run();
  BlynkRun();
  delay(100);
}

// Methode für Refresh-Timer
void refresh() {
  readSensor();
  readDHT();
  displayData();
  LEDStatus();
  writeDataSerial();
}
void upload(){
  uploadBlynk();
  char empty[] = "";
  if (memcmp(serverName, empty, 1)) {
    // Eigener Server
    uploadServer();
  }   
}