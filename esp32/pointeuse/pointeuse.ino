#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define SS_PIN  5
#define RST_PIN 4
#define LED_PIN 2

// ---- À MODIFIER ----
const char* WIFI_SSID = "SFR_F2CF"; 
const char* WIFI_PASS = "b43wf8svw9d5u3x4sz4s";                 // remets ton mot de passe
const char* API_URL   = "http://192.168.1.213:8000/api/scan"; // IP du PC qui fait tourner le serveur
const char* ZONE      = "Salle serveur";

// ---- IP FIXE DE L'ESP32 (à adapter) ----
IPAddress local_IP(192, 168, 1, 150);   // l'IP que tu veux donner à l'ESP32 (doit être libre)
IPAddress gateway(192, 168, 1, 254);    // passerelle du réseau Wi-Fi
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192, 168, 1, 254);

MFRC522 rfid(SS_PIN, RST_PIN);

String nuidToString();   // déclaration de la fonction utilitaire

void setup() {
  Serial.begin(9600);
  delay(500);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  SPI.begin();
  rfid.PCD_Init();
  delay(100);

  // Configuration de l'IP fixe (avant WiFi.begin)
  if (!WiFi.config(local_IP, gateway, subnet, dns)) {
    Serial.println("Echec config IP fixe");
  }

  // Connexion Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connexion Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.print("\nIP ESP32 : ");
  Serial.println(WiFi.localIP());
  Serial.print("Passerelle : ");
  Serial.println(WiFi.gatewayIP());
  Serial.println(String("API : ") + API_URL);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial())   return;

  // Lecture réussie : LED 500 ms
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);

  // Envoi du NUID au serveur
  String nuid = nuidToString();
  Serial.println("NUID : " + nuid);

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(API_URL);
    http.addHeader("Content-Type", "application/json");
    String body = "{\"nuid\":\"" + nuid + "\",\"zone\":\"" + ZONE + "\"}";
    int code = http.POST(body);
    Serial.printf("HTTP %d (%s) : %s\n", code, http.errorToString(code).c_str(), http.getString().c_str());
    http.end();
  } else {
    Serial.println("Wi-Fi deconnecte");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(1000);   // évite d'envoyer plusieurs fois le même passage
}

/**
 * Fonction utilitaire pour extraire le NUID sous forme de String de la
 * variable globale rfid. */
String nuidToString() {
  String s = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) s += "0";
    s += String(rfid.uid.uidByte[i], HEX);
  }
  s.toUpperCase();
  return s;
}