#include "stille-nacht.h"

#define DOORBELL 2
#define LED_CYCLE_1 10
#define LED_CYCLE_2 5
#define RGB_R 6
#define RGB_G 7
#define RGB_B 8
#define BUZZER 3

void dimLED(uint8_t led, uint8_t interval, uint32_t delay)
{
  unsigned int time = ((millis() / 4) - delay) % (interval * 2);
  analogWrite(led, time);
}

void rbgLED(uint8_t red, uint8_t green, uint8_t blue)
{
  unsigned int time = millis() % 4800;
  digitalWrite(red, time > 700 && time < 2800 ? HIGH : LOW);
  digitalWrite(green, time > 2100 && time < 4200 ? HIGH : LOW);
  digitalWrite(blue, time < 1400 || time > 3500 ? HIGH : LOW);
}

void setup()
{
  Serial.begin(9600);
  pinMode(DOORBELL, INPUT_PULLUP);
  pinMode(RGB_B, OUTPUT);
  pinMode(RGB_R, OUTPUT);
  pinMode(RGB_G, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(DOORBELL), ringDoorbell, RISING);
}

void ringDoorbell()
{
  start(BUZZER);
}

void loop()
{
  boolean playing = async_play();
  if (playing)
  {
    dimLED(LED_CYCLE_1, 255, 254);
    dimLED(LED_CYCLE_2, 255, 127);
    rbgLED(RGB_R, RGB_G, RGB_B);
  }
  else
  {
    digitalWrite(RGB_R, LOW);
    digitalWrite(RGB_G, LOW);
    digitalWrite(RGB_B, LOW);
    digitalWrite(LED_CYCLE_1, LOW);
    digitalWrite(LED_CYCLE_2, LOW);
  }
}