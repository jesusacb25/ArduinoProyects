// Incluye las librerías necesarias para la conexión WiFi y el servidor web asíncrono.
#include <WiFi.h>
#include <ESPAsyncWebSrv.h> 
#include "data.h"

// Nombre de la red WiFi y su contraseña.
const char *ssid = "CLARO_WIFIB00";
const char *password = "CLAROIB00";

// Definición de pines para los sensores y los LEDs.
int fotoceldaPin = 33;
int potenciometroPin = 34;
int led1Pin = 32;
int led2Pin = 25;
int led3Pin = 26;

// Crea un objeto para el servidor web en el puerto 80.
AsyncWebServer server(80);

// Configuración inicial del dispositivo.
void setup() {
  // Inicia la comunicación serial a una velocidad de 115200 baudios.
  Serial.begin(115200);

  // Configura los pines como entrada o salida según sea necesario.
  pinMode(fotoceldaPin, INPUT);
  pinMode(potenciometroPin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);

  // Conecta el dispositivo a la red WiFi utilizando el nombre y la contraseña proporcionados.
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Muestra un mensaje indicando que el dispositivo está conectado a la red WiFi y muestra la dirección IP asignada.
  Serial.println("Conectado a la red WiFi");
  Serial.println("Dirección IP: " + WiFi.localIP().toString());

  // Configura los manejadores de ruta para el servidor web.

  // Cuando se accede al servidor raíz ("/"), envía el contenido de un archivo HTML almacenado en memoria flash.
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String response = FPSTR(index_html);
    request->send(200, "text/html", response);
  });

  // Cuando se accede a la ruta "/values", envía un objeto JSON con los valores de los sensores.
  server.on("/values", HTTP_GET, [](AsyncWebServerRequest *request){
    int fotoceldaValue = analogRead(fotoceldaPin);
    int potenciometroValue = analogRead(potenciometroPin);
    String jsonValues = "{\"fotocelda\":" + String(fotoceldaValue) + ",\"potenciometro\":" + String(potenciometroValue) + "}";
    request->send(200, "application/json", jsonValues);
  });

  // Inicia el servidor web.
  server.begin();
}

// Función principal que se ejecuta en un bucle infinito.
void loop() {
  // Lee los valores de los sensores (fotocelda y potenciómetro).
  int fotoceldaValue = analogRead(fotoceldaPin);
  int potenciometroValue = analogRead(potenciometroPin);

  // Controla los LEDs en función del valor del potenciómetro.
  digitalWrite(led1Pin, potenciometroValue >= 1365 ? HIGH : LOW);
  digitalWrite(led2Pin, potenciometroValue >= 2730 ? HIGH : LOW);
  digitalWrite(led3Pin, potenciometroValue == 4095 ? HIGH : LOW);
  
  delay(2000); // Espera 2 segundos antes de volver a leer los valores de los sensores y actualizar los LEDs.
}
