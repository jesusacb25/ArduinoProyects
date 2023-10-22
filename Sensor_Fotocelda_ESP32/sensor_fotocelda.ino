int LDR = 33;
int VALOR = 0;
void setup() {
  pinMode(LDR , INPUT);
  Serial.begin(115200);

}

void loop() {
  // Lee el valor del sensor de luz (LDR)
  int VALOR = analogRead(LDR);  // Suponiendo que el pin del LDR está conectado al pin analógico A0

  // Imprime el valor del sensor en el puerto serie
  Serial.print("El valor es: ");
  Serial.println(VALOR);

  // Compara el valor leído y muestra un mensaje en función de la cantidad de luz
  if (VALOR > 1000 && VALOR < 3000) {
    Serial.println("Hay luz");
  } else if (VALOR > 3000) {
    Serial.println("Hay mucha luz");
  } else {
    Serial.println("Hay poca luz");
  }

  // Espera 1 segundo antes de leer el sensor nuevamente
  delay(1000);
}
