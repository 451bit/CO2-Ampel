# CO2-Ampel
ESP32 basierte CO2-Ampel für Schulen
## Inhalt
* Bau
* Programmierung
* Blynk einrichten
* Case
## Bau
* Die Pinleisten von beiden Seiten unten an den ESP anlöten. VORSICHT bei den Pins am Anschlusskabel des Displays. Der Lötkolben darf das Kabel auf keinen Fall berühren. Darauf achten, dass die Pinleisten möglichst vertikel stehen.

![Bild 1](/Bilder/01.jpg)
![Bild 2](/Bilder/02.jpg)

* Mit einem Multimeter an allen benachbarten Pins sicherstellen, dass keine Verbindung zwischen den Pins besteht (Widerstand sehr hoch)
* Die Pinleiste vom DHT22 mit einer Zange abknipsen und die Pin-Rest aus den Löchern entfernen.

![Bild 3](/Bilder/03.jpg)
![Bild 4](/Bilder/04.jpg)

* Den Stecker-Anschluss vom Z19B mit einer Zange abknipsen.

![Bild 5](/Bilder/05.jpg)
![Bild 6](/Bilder/06.jpg)

* Abstandsbolzen von unten an die Platine schrauben <br>

![Bild 7](/Bilder/07.jpg)

WICHTIGE HINWEISE: Die Verkabelung exakt einhalten, ansonsten passt das Case evtl. nicht.

* Den ESP, die Widerstände und die LEDs nach dem Schaltbild auf der Platine verlöten.
 * LED-Beine möglichst lang lassen, damit die LEDs variabel im Case plaziert werden können und darauf achten, dass die Kathode (kurzes Beinchen, abgeflachte Seite) wie im Schaltbild rechts ist/mit Widerstand und Gnd/- verbunden ist.
 
![Bild 8](/Bilder/08.jpg)
 
 * Den ESP komplett in die Platine einlassen und von der Unterseite verlöten (ansonsten sitzt er zu hoch für das Case)
 
![Bild 9](/Bilder/09.jpg)
 
* Alle Kabelverbindungen auf der Unterseite der Platine verlöten. Sollte auf der Rückseite der Platine gemacht werden (Auf dem Bild sind 5V- und GND- Leiste anders als im Schaltbild verlötet).

![Bild 10](/Bilder/10.jpg)

* Für den DHT22 drei und den Z19B vier relativ lange Kabel (ca. 10 cm) wählen (sie werden nicht direkt auf der Platine verlötet) und nach dem Schaltplan an die Unterseite der Sensoren und auf die Platine löten.

![Bild 11](/Bilder/11.jpg)

## Programmierung
* Arduino-IDE herunterladen (https://www.arduino.cc/)
* Repos in der IDE einbinden:
  * Datei -> Voreinstellungen
  * Bei "Zusätzliche Boardverwalter-URLs" folgendes Einfügen: https://resource.heltec.cn/download/package_heltec_esp32_index.json
* Board auswählen
  * Werkzeuge -> Board -> Boardverwalter
  * Suche nach "Heltec ESP32"
  * "Heltec ESP32 Series Dev-boards" installieren und Boardverwalter schließen
  * Werkzeuge -> Board -> Heltec ESP32 Arduino -> WiFi Kit 32
* Bibliotheken einbinden
  * Werkzeuge -> Bibliotheken verwalten
  * Folgende Bibliotheken installieren:
    * Blynk
    * DHT sensor library
    * ESP32 AnalogWrite
    * Heltec ESP32 Dev-Boards
    * SimpleTimer
* Den ESP per USB-Kabel mit dem PC verbinden und unter Werkzeuge -> Port den korrekten COM-Port für den ESP wählen (meist nicht COM1) 
* Arduino-Code herunterladen und die Datei CO2-Ampel.ino in der Arduino-IDE öffnen.
* In der Hauptdatei CO2-Ampel.ino müssen folgende Daten eingetragen werden:
  * BlynkServer[], BlynkServerPort[] (optional, nur falls ein eigener Server verwendet wird) 
  * auth[]: Hier den Auth-Token aus der Blynk-App eintragen (s. unten)
  * SSID/WIFI_PW 1-3: Hier die SSIDs und Passwörter für 3 verschiene Netzwerke eingeben (Zuhause, Schule, ...)
  * ggf Pinbelegung ändern
  * Unter Timer können die Timer angepasst werden
* Sketch auf den ESP übertragen
## Blynk einrichten
* Blynk-App herunterladen
* Login oder Account erstellen
* Neues Projekt erstellen
  * Projektname wählen
  * Als Device ESP32 Dev Board wählen
  * Create
* Oben auf die Mutter klicken und den Auth Token per Mail senden lassen. Diesen Token in der CO2-Ampel.ino bei auth[] eintragen
* Mit dem "Plus" Elemente auf der Oberfläche hinzufügen
  * z.B. Labeled Value zur Anzeige der CO2-Konzentration.
  * Als Input V0 wählen und Aktualisierungsrate auf 10 sec
  * Die weiteren Werte:
    * V0: CO2
    * V1: Temp
    * V2: Feuchtigkeit
  * Butten zum Neustart (V11) oder Kalibrieren (V10) hinzufügen
* Oben rechts "Start"-Knopf
* Wenn eigener Blynk-Server verwendet wird (https://github.com/blynkkk/blynk-server) dann in der CO2-Ampel.ino "BlynkServer[]" und "BlynkServerPort[]" anpassen. 
## Case
* 3D-Modell-Vorlage herunterladen und nach eigenen Wünschen anpassen
* Board auf dem Boden verschrauben
* Sensoren von innen durch die Öffnungen stecken und mit Heißkleber fixieren.
* Deckel aufsetzen, hierbei darauf achten, dass die LEDs durch die Löcher passen
