//### Código Arduino

//```cpp
// EXP-01 — Estar en la cárcel
// Concepto: libre albedrío suspendido por el sistema
// Arduino Mega 2560

#include <Servo.h>

Servo servo;

const int PIN_SERVO    = 9;
const int PIN_POT      = A0;
const int PIN_BOTON    = 2;
const int PIN_LED_VRD  = 4;   // Libre albedrío
const int PIN_LED_ROJO = 5;   // Bloqueado

bool      bloqueado       = false;
int       posicionActual  = 90;
int       tiempoCarcel    = 0;
unsigned long inicioCaptura = 0;

void setup() {
  servo.attach(PIN_SERVO);
  pinMode(PIN_BOTON,    INPUT);
  pinMode(PIN_LED_VRD,  OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);
  servo.write(90);
  Serial.begin(9600);
  Serial.println("{\"estado\":\"LIBRE\",\"posicion\":90,\"tiempo_carcel\":0}");
}

void loop() {
  bool botonPresionado = digitalRead(PIN_BOTON);

  // Botón activa y desactiva el modo cárcel
  if (botonPresionado && !bloqueado) {
    bloqueado    = true;
    inicioCaptura = millis();
    posicionActual = servo.read();  // Congela la posición actual
    digitalWrite(PIN_LED_ROJO, HIGH);
    digitalWrite(PIN_LED_VRD,  LOW);
    delay(300); // Antirrebote
  } else if (botonPresionado && bloqueado) {
    bloqueado = false;
    digitalWrite(PIN_LED_ROJO, LOW);
    digitalWrite(PIN_LED_VRD,  HIGH);
    tiempoCarcel = 0;
    delay(300);
  }

  if (bloqueado) {
    // El potenciómetro genera señal pero el servo NO responde
    int voluntad = map(analogRead(PIN_POT), 0, 1023, 0, 180);
    // La voluntad existe pero el sistema la ignora
    tiempoCarcel = (millis() - inicioCaptura) / 1000;

    // El servo permanece en la posición de la captura
    servo.write(posicionActual);

    Serial.print("{\"estado\":\"CARCEL\"");
    Serial.print(",\"voluntad\":");   Serial.print(voluntad);
    Serial.print(",\"posicion\":");   Serial.print(posicionActual);
    Serial.print(",\"tiempo_carcel\":"); Serial.print(tiempoCarcel);
    Serial.println("}");

  } else {
    // Modo libre: el potenciómetro controla el servo
    int angulo = map(analogRead(PIN_POT), 0, 1023, 0, 180);
    servo.write(angulo);

    Serial.print("{\"estado\":\"LIBRE\"");
    Serial.print(",\"voluntad\":");  Serial.print(angulo);
    Serial.print(",\"posicion\":"); Serial.print(angulo);
    Serial.print(",\"tiempo_carcel\":0}");
    Serial.println();

    digitalWrite(PIN_LED_VRD, HIGH);
    digitalWrite(PIN_LED_ROJO, LOW);
  }

  delay(100);
}
