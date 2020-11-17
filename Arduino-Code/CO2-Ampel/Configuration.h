// Daten für Blynk
#define BlynkServerConfig ""  // Hier eingenen Blynk-Server eintragen oder leer "" lassen
#define BlynkServerPortConfig 9443  // Port für Blynk-Server
//#define BLYNK_SSL_USE_LETSENCRYPT // diese Zeile nur aktivieren, wenn für den eigenen Blynk-Server ein Letsencrypt-Certifikat verwendet wird
#define  BlynkAuthConfig "******" // Blynk-Auth-Code aus der App

// Daten für HTTP-Server
#define  SensorLocationConfig "OrtDesSensors" // Bezeichnung des Gebäudes oder Raums für den Sensor
#define  SensorNameConfig "SensorName"  // Eindeutiger Name für den Sensor
#define  ApiKeyValueConfig "******" // ApiKey für den Upload auf den Server (identisch mit ApiKey in readData.php)
#define  ServerNameConfig "https://pfad.zur/readData.php" // URL zur readData.php

// WIFIs
#define  SSID1Config "SsidWlan1"  // SSID für Wifi 1 (z.B. in der Schule)
#define  WiFiPwConfig1 "******"             // Passwort für Wifi 1
#define  SSID2Config ""     // SSID für Wifi 2 (z.B. zuhause)
#define  WiFiPwConfig2 "" // Passwort für Wifi 2
#define  SSID3Config ""               // SSID für Wifi 3
#define  WiFiPwConfig3 ""             // // Passwort für Wifi 3
