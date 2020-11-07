# CO2-Ampel
ESP32 basierte CO2-Ampel für Schulen
## Inhalt
* Bau
* Programmierung
* Blynk Einrichten
* Case
## Bau
* Die Pinleisten von beiden Seiten unten an den ESP anlöten.
* Die Pinleiste vom DHT22 mit einer Zange abknipsen und die Pin-Rest aus den Löchern entfernen.
* Den Stecker-Anschluss vom Z19B mit einer Zange abknipsen.
* Den ESP, die Widerstände und die LEDs nach dem Schaltplan auf der Platine verlöten (LED-Beine möglichst lang lassen). Alle Kabelverbindungen auf der Platine verlöten.
* Für den DHT22 drei und den Z19B vier relativ lange Kabel (ca. 10 cm) wählen (sie werden nicht direkt auf der Platine verlötet) und nach dem Schaltplan an die Sensoren und auf die Platine löten.
## Programmierung
* Arduino-IDE herunterladen (https://www.arduino.cc/)
* Repos in der IDE einbinden:
  * Datei -> Voreinstellungen
  * Bei "Zusätzliche Boardverwalter-URLs" folgendes Einfügen: https://resource.heltec.cn/download/package_heltec_esp32_index.json
* Board auswählen
  * Werkzeuge -> Board -> Boardverwalter
  * Suche nach "Heltec ESP32"
  * "Heltec ESP32 Series Dev-boards" installieren und Boardverwalter schließen
  * Werkzeute -> Board -> Heltec ESP32 Arduino -> WiFi Kit 32
* Bibliotheken einbinden
  * Werkzeuge -> Bibliotheken verwalten
  * Folgende Bibliotheken installieren:
    * Blynk
    * DHT sensor library
    * ESP32 AnalogWrite
    * Heltec ESP32 Dev-Boards
    * SimpleTimer
* Arduino-Code herunterladen
* In der Hauptdatei Webkit32CO2.ino müssen folgende Daten eingetragen werden:
  * BlynkServer[], BlynkServerPort[] (optional, nur falls ein eigener Server verwendet wird) 
  * auth[]: Hier den Auth-Token aus der Blynk-App eintragen (s. unten)
  * SSID/WIFI_PW 1-3: Hier die SSIDs und Passwörter für 3 verschiene Netzwerke eingeben (Zuhause, Schule, ...)
  * ggf Pinbelegung ändern
  * Unter Timer können die Timer angepasst werden
## Blynk einrichten
* Blynk-App herunterladen
* Login oder Account erstellen
* Neues Projekt erstellen
  * Projektname wählen
  * Als Device ESP32 Dev Board wählen
  * Create
* Oben auf die Mutter klicken und den Auth Token per Mail senden lassen. Diesen Token in der Webkit32.ino-Datei bei auth[] eintragen
* Mit dem "Plus" Elemente auf der Oberfläche hinzufügen
  * z.B. Labeled Value zur Anzeige der CO2-Konzentration.
  * Als Input V0 wählen und Aktualisierungsrate auf 10 sec
  * Die weiteren Werte:
    * V0: CO2
    * V1: Temp
    * V2: Feuchtigkeit
  * Butten zum Neustart (V11) oder Kalibrieren (V10) hinzufügen
* Oben rechts "Start"-Knopf
* Wenn eigener Blynk-Server verwendet wird (https://github.com/blynkkk/blynk-server) dann in der Webkit32CO2.ino "BlynkServer[]" und "BlynkServerPort[]" anpassen. 
## Case
* 3D-Modell-Vorlage herunterladen und nach eigenen Wünschen anpassen
* Board auf dem Boden verschrauben
* Sensoren von innen durch die Öffnungen stecken und mit Heißkleber fixieren
