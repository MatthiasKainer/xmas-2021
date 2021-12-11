#include "stille-nacht.h" 

#define DOORBELL 2


void dimLED(uint8_t led, uint8_t interval, uint32_t delay)
{
  unsigned int time = ((millis() / 4) - delay) % (interval * 2);
  analogWrite(led, time);
}

void setup()
{
  Serial.begin(9600); 
  pinMode(DOORBELL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(DOORBELL), ringDoorbell, RISING);
}

void ringDoorbell() {
  start();
}

void loop()
{
  async_play();
  dimLED(10, 255, 254);
  dimLED(5, 255, 127);
}