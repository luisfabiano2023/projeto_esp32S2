const int trigPin = 22;
const int echoPin = 23;
const int relayPin = 32; // Define o pino do relé

// Define a velocidade do som em cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

// Define as constantes de distância
const int distanceThresholdOn = 30;  // Distância para ligar o relé
const int distanceThresholdOff = 50; // Distância para desligar o relé

void setup() {
  Serial.begin(74880);      // Inicia a comunicação serial
  pinMode(trigPin, OUTPUT); // Define o trigPin como saída
  pinMode(echoPin, INPUT);  // Define o echoPin como entrada
  pinMode(relayPin, OUTPUT); // Define o relayPin como saída

  // Inicializa o relé desligado
  digitalWrite(relayPin, LOW);
}

void loop() {
  // Limpa o trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Define o trigPin em HIGH por 10 microsegundos
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lê o echoPin, retorna o tempo de viagem da onda sonora em microsegundos
  duration = pulseIn(echoPin, HIGH);

  // Calcula a distância
  distanceCm = duration * SOUND_SPEED / 58;

  // Exibe a distância no Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  // Controla o relé com base na distância medida
  if (distanceCm > distanceThresholdOn && distanceCm < distanceThresholdOff) {
    digitalWrite(relayPin, HIGH); // Liga o relé
    Serial.println("Ligando..........");
    
  } else if (distanceCm > distanceThresholdOff) {
    digitalWrite(relayPin, LOW);  // Desliga o relé
  }

  // Aguarda 1000 milissegundos antes de medir novamente
  delay(1000);
}
