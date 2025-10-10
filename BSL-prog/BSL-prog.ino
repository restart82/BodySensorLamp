#define SENSOR_PIN  PD2   // Дискретный вход
#define LED_PIN     PB2   // ШИМ
#define TIMEOUT     (20 * 60 * 1000UL)  // Время работы лампы, мс
#define LED_POWER   50  // Мощность ШИМ, %

int pwmPower        = 0;
long int time       = 0;
bool ledIsWork      = false;

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  pwmPower = 255 * LED_POWER / 100;
  analogWrite(LED_PIN, 0);
}

void loop() {
  if (digitalRead(SENSOR_PIN)) {
    time = millis();
    if (!ledIsWork) {
      analogWrite(LED_PIN, pwmPower);
      ledIsWork = true;
    }
  }

  if (ledIsWork && (millis() - time >= TIMEOUT)) {
    analogWrite(LED_PIN, 0);
    ledIsWork = false;
  }

  delay(100);
}
