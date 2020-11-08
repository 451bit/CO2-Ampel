/*
  CO2-Ampel

  ESP32 liest CO2-, Temperatur- und Feuchtigkeit aus und zeigt die Werte auf dem Display an. Anhand des CO2-Wertes ändert sich zudem 
  die Farbe der LEDs.
  Optinal können die Daten zu einem Blynk-Server hochgeladen werden.


  Created 08 11 2020
  By Philipp Watermann
  
  https://github.com/451bit/CO2-Ampel

*/

#include <Arduino.h>
//#define BLYNK_SSL_USE_LETSENCRYPT
#include "heltec.h"
#include <WiFiMulti.h>
#include <BlynkSimpleEsp32_SSL.h>
#include <ArduinoOTA.h>
#include <analogWrite.h>
#include "DHT.h"
// Temp-Sensor Typ
#define DHTTYPE DHT22

// Blynk Daten
// BlynkServer und -Port leer lassen, falls der Standard-Blynk-Server verwendet werden soll. Ansonsten die URL und Port des eigenen Servers eintragen
// Wenn auf dem eigenen Server ein LetsEncrypt-Zertifikat verwendet wird, dann Zeile 2 "#define BLYNK_SSL_USE_LETSENCRYPT" auskommentieren
char BlynkServer[] = "";
uint16_t BlynkServerPort = 9443;
char auth[] = "abcdefg1234";


// HIER DIE WIFI-DATEN EINGEBEN
String SSID_1 = "************";
String WIFI_PW_1 = "************";
String SSID_2 = "************";
String WIFI_PW_2 = "************";
String SSID_3 = "************";
String WIFI_PW_3 = "************";

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
int TimerWarmup = 180; // Warumup-Timer
SimpleTimer TimerRefresh; // Timer zum Aktualisieren der Daten
int TimerRefreshInterval = 10;
SimpleTimer TimerWifi; // Timer zur Prüfung der Netzwerkverbindung
int TimerWifiInterval = 10;

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
  initWifiBlynk();
  warumup();
  TimerRefresh.setInterval(TimerRefreshInterval * 1000, refresh);
}

// OTA und Timer abfragen
void loop() {
  ArduinoOTA.handle();
  TimerRefresh.run();
  TimerWifi.run();
  delay(1000);
}

// Methode für Refresh-Timer
void refresh() {
  readSensor();
  readDHT();
  displayData();
  LEDStatus();
  writeDataSerial();
}
