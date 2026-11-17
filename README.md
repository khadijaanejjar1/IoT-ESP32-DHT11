Lecture d'un capteur de température et d'humidité (DHT11)

## 1. Présentation du projet

Ce projet consiste à réaliser un système IoT basé sur une carte ESP32 et un capteur DHT11.
Le système permet de mesurer la température et l'humidité de l'environnement, de transmettre les données à travers un réseau Wi-Fi et de les afficher en temps réel sur une page Web.

## 2. Objectif

L'objectif principal est de concevoir un nœud IoT capable de :
- Acquérir la température et l'humidité à l'aide du capteur DHT11.
- Traiter les mesures avec la carte ESP32.
- Connecter l'ESP32 à un réseau Wi-Fi.
- Héberger un serveur Web sur l'ESP32.
- Afficher les mesures sur une interface Web avec actualisation automatique.

## 3. Matériel utilisé

- Carte ESP32.
- Capteur DHT11.
- Breadboard.
- Fils de connexion .
- Câble USB.
- Ordinateur.

## 4. Logiciels et bibliothèques

- Arduino IDE.
- Bibliothèque WiFi.h.
- Bibliothèque WebServer.h.
- Bibliothèque DHT sensor library.
- Bibliothèque Adafruit Unified Sensor.

## 5. Architecture du système

Le fonctionnement du système suit les étapes suivantes :

1. Le capteur DHT11 mesure la température et l'humidité.
2. L'ESP32 récupère les mesures.
3. L'ESP32 se connecte au réseau Wi-Fi.
4. Le serveur Web intégré à l'ESP32 reçoit les requêtes HTTP.
5. Les mesures sont transmises au navigateur au format JSON.
6. La page Web affiche automatiquement les valeurs.



## 6. Résultat attendu

Le système doit permettre :
- D'afficher la température en degrés Celsius.
- D'afficher l'humidité en pourcentage.
- De consulter les mesures depuis un navigateur Web.
- D'actualiser automatiquement les mesures toutes les deux secondes.

## 7. Conclusion

Ce travail pratique m a permis de découvrir les principes fondamentaux de l'Internet des objets. J'ai réalisé un système capable d'acquérir des données physiques à l'aide d'un capteur DHT11, de les traiter avec un ESP32 et de les transmettre par Wi-Fi vers une interface Web.

