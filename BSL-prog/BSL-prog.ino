#include <util/delay.h>

#define SENSOR_PIN  4   // Дискретный вход
#define LED_PIN     3   // ШИМ

#define SECONDS     0
#define MINUTES     0
#define TIMEOUT     ((MINUTES * 60 + SECONDS) * 1000UL)  // Время работы лампы, мс

long time           = 0;
bool ledIsWork      = false;
void testBlink();

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  TCCR2A |= _BV(WGM20) | _BV(WGM21);
  TCCR2B =  (TCCR2B & 0b11111000) | 0x01;
  pinMode(LED_PIN, OUTPUT);

  analogWrite(LED_PIN, 0);
}

void loop() {
  if (digitalRead(SENSOR_PIN) == LOW) {
    time = millis();
    if (!ledIsWork) {
      analogWrite(LED_PIN, 1);
      ledIsWork = true;
    }
    // testBlink();
  }
  

  if (ledIsWork && (millis() - time > TIMEOUT)) {
    analogWrite(LED_PIN, 0);
    ledIsWork = false;
  }

  _delay_ms(500);
}


void testBlink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}