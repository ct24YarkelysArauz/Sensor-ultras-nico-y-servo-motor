#include <ESP32Servo.h>  // Librería para controlar el servo

// Definimos los pines del sensor ultrasónico
#define TRIG_PIN 12
#define ECHO_PIN 14

// Definimos el pin para el servo motor
#define SERVO_PIN 13

Servo miServo;

// Función para medir la distancia con el sensor ultrasónico
long medirDistancia() {
  // Aseguramos que el pin TRIG esté en bajo antes de comenzar
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Enviamos un pulso de 10 microsegundos para activar el sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Leemos el tiempo que tarda el pulso en regresar al ECHO
  long duracion = pulseIn(ECHO_PIN, HIGH);

  // Calculamos la distancia en centímetros (velocidad del sonido es 343 m/s)
  long distancia = (duracion / 2) * 0.0343;

  return distancia;
}

void setup() {
  // Inicializamos la comunicación serial
  Serial.begin(115200);
  
  // Configuramos los pines del sensor ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Inicializamos el servo motor
  miServo.attach(SERVO_PIN);
}

void loop() {
  // Medimos la distancia con el sensor ultrasónico
  long distancia = medirDistancia();
  
  // Mostramos la distancia medida en el monitor serial
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Mapeamos la distancia a un rango de ángulos para el servo (por ejemplo de 0° a 180°)
  int angulo = map(distancia, 5, 100, 0, 180);  // Rango entre 5 y 100 cm mapeado a 0-180 grados
  angulo = constrain(angulo, 0, 180);  // Aseguramos que el ángulo esté entre 0 y 180 grados
  
  // Movemos el servo al nuevo ángulo
  miServo.write(angulo);

  // Esperamos un momento antes de hacer otra lectura
  delay(500);
}
