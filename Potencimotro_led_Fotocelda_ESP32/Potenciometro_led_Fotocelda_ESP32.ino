const int potPin = 34;
int pinLed1 = 32;
int pinLed2 = 33;
int pinLed3 = 25;
int pinLed4 = 26;
int potValor = 0; 

void setup() {
  //se inicializa el puerto
  Serial.begin(115200);
  //se inicializa las salidas led
  pinMode(pinLed1 , OUTPUT);
  pinMode(pinLed2 , OUTPUT);
  pinMode(pinLed3 , OUTPUT);
  pinMode(pinLed4, OUTPUT);
  delay(1000);

}

void loop() {
  potValor  = analogRead(potPin);
  Serial.println(potValor);

  if(potValor >= 800){
    digitalWrite(pinLed1 , HIGH);
  }else{
    digitalWrite(pinLed1 , LOW);
  }
  if(potValor >= 1700){
    digitalWrite(pinLed2 , HIGH);
  }else{
    digitalWrite(pinLed2 , LOW);
  }
  if(potValor >= 3000){
    digitalWrite(pinLed3 , HIGH);
  }else{
    digitalWrite(pinLed3 , LOW);
  }
  if(potValor >= 4095){
    digitalWrite(pinLed4 , HIGH);
  }else{
    digitalWrite(pinLed4 , LOW);
  }

  delay(100);
}
