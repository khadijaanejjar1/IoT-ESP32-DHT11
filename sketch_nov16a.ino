
// ==========================================
//  ESP32 + DHT11 + Wi-Fi + WEB
// ==========================================

// 1. Inclusion des bibliotheques
#include <WiFi.h>             //permet à l'ESP32 de se connecter au réseau Wi-Fi.
#include <WebServer.h>        //permet de créer un serveur Web sur l'ESP32.
#include "DHT.h"             //permet de communiquer avec le capteur DHT11

// 2. Configuration du capteur DHT11
#define DHTPIN 27          //indique que le fil DATA du capteur est connecté au GPIO 27
#define DHTTYPE DHT11      //indique le modèle du capteur utilisé

DHT dht(DHTPIN, DHTTYPE);   //crée un objet appelé dht qui permet de commander le capteur et de récupérer ses mesures.

// 3. Informations du reseau Wi-Fi
const char* ssid = "vivo";
const char* password = "123456789";

// 4. Creation du serveur Web sur le port 80
WebServer server(80);     

// 5. Creation de la page Web
const char page[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Surveillance IoT</title>

  <style>
    body {
      font-family: Arial;
      text-align: center;
      background-color: #eef2f7;
      padding: 20px;
    }

    h1 {
      color: #1565c0;
    }

    .card {
      background-color: white;
      padding: 20px;
      margin: 20px auto;
      max-width: 350px;
      border-radius: 12px;
      box-shadow: 0 2px 8px #cccccc;
    }

    .value {
      font-size: 30px;
      color: #00897b;
      font-weight: bold;
    }
  </style>
</head>

<body>

  <h1>Systeme de surveillance IoT</h1>

  <div class="card">
    <h2>Temperature</h2>
    <p class="value" id="temperature">-- °C</p>
  </div>

  <div class="card">
    <h2>Humidite</h2>
    <p class="value" id="humidite">-- %</p>
  </div>

  <p id="etat">Connexion aux mesures...</p>

  <script>

    async function actualiserMesures() {

      try {

        const reponse = await fetch('/data');

        if (!reponse.ok) {
          throw new Error("Erreur serveur");
        }

        const donnees = await reponse.json();

        document.getElementById("temperature").textContent =
          donnees.temperature + " °C";

        document.getElementById("humidite").textContent =
          donnees.humidite + " %";

        document.getElementById("etat").textContent =
          "Mesures actualisees";

      } catch (erreur) {

        document.getElementById("etat").textContent =
          "Erreur de communication";

      }
    }

    actualiserMesures();

    setInterval(actualiserMesures, 2000);

  </script>

</body>
</html>
)rawliteral";

// 6. Fonction pour afficher la page Web
void handleRoot() {

  server.send(200, "text/html", page);

}

// 7. Fonction pour envoyer les mesures du capteur
void handleData() {

  float temperature = dht.readTemperature();

  float humidite = dht.readHumidity();

  if (isnan(temperature) || isnan(humidite)) {

    server.send(500, "application/json",
                "{\"error\":\"Erreur de lecture du capteur\"}");

    return;
  }

  String donnees = "{\"temperature\":";
  donnees += String(temperature, 1);
  donnees += ",\"humidite\":";
  donnees += String(humidite, 1);
  donnees += "}";

  server.send(200, "application/json", donnees);

}

// 8. Fonction d'initialisation
void setup() {

  Serial.begin(115200);

  dht.begin();

  // Connexion au Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connexion au Wi-Fi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.println();

  Serial.println("Wi-Fi connecte !");

  Serial.print("Adresse IP : ");

  Serial.println(WiFi.localIP());

  // Configuration des routes Web
  server.on("/", handleRoot);

  server.on("/data", handleData);

  // Demarrage du serveur
  server.begin();

  Serial.println("Serveur Web demarre !");

}

// 9. Boucle principale
void loop() {

  server.handleClient();

}
