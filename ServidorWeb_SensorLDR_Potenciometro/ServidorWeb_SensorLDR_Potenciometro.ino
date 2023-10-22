#include <WiFi.h>

const char *ssid = "CLARO_WIFIB00";
const char *password = "CLAROIB00";

int fotoceldaPin = 33; // Pin de la fotocelda (cambiar al pin correcto)
int potenciometroPin = 34; // Pin del potenciómetro (cambiar al pin correcto)
int led1Pin = 32; // Pin del LED 1
int led2Pin = 25; // Pin del LED 2
int led3Pin = 26; // Pin del LED 3

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(fotoceldaPin, INPUT);
  pinMode(potenciometroPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Conectado a la red WiFi");
  Serial.println("Dirección IP: " + WiFi.localIP().toString());

  server.begin();
}

void loop() {
  int fotoceldaValue = analogRead(fotoceldaPin);
  int potenciometroValue = analogRead(potenciometroPin);

  if (potenciometroValue >= 1365) {
    digitalWrite(led1Pin, HIGH);
  } else {
    digitalWrite(led1Pin, LOW);
  }

  if (potenciometroValue >= 2730) {
    digitalWrite(led2Pin, HIGH);
  } else {
    digitalWrite(led2Pin, LOW);
  }

  if (potenciometroValue == 4095) {
    digitalWrite(led3Pin, HIGH);
  } else {
    digitalWrite(led3Pin, LOW);
  }

  WiFiClient client = server.available();
  if (client) {
    String response = "HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\n\n";
    response += "<html><body>";
    response += "<center>";
    response += "<h1>ESP32 Web Server</h1>";
    response += "<p>Fotocelda: " + String(fotoceldaValue) + "</p>";
    response += "<p>Potenciometro: " + String(potenciometroValue) + "</p>";
    response += "</center>";
    response += "<script>";
    response += "setInterval(function () {";
    response += "location.reload();";
    response += "}, 500);";
    response += "</script>";
    response += "</body></html>";
    client.print(response);
    client.flush();
    delay(10);
    client.stop();

  }

  delay(100); // Espera 1 segundo antes de actualizar la página web y leer nuevamente los valores.
}
