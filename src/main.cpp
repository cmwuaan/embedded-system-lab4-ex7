#include <Arduino.h>

#define soundPin 4

byte ledPins[] = {2, 3};
byte pinCount;

int clapCount = 0;
unsigned long detection_time = 0;
unsigned long detection_start_time = 0;

void turnOnLights(int);
void turnOffAllLights();

void setup()
{
  Serial.begin(9600);
  turnOffAllLights();
}

void loop()
{

  int soundStatus = digitalRead(soundPin);
  if (soundStatus)
  {
    if (clapCount == 0)
    {
      detection_time = detection_start_time = millis();
      clapCount++;
    }
    else if (clapCount > 0 && millis() - detection_time >= 200)
    {
      detection_time = millis();
      clapCount++;
    }

    if (clapCount > 2)
    {
      clapCount = 3;
    }
    Serial.println(clapCount);
  }

  if (millis() - detection_start_time >= 1000)
  {
    turnOnLights(clapCount);
    clapCount = 0;
  }
}

void turnOnLights(int numLights)
{
  switch (numLights)
  {
  case 1:
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], LOW);
    break;
  case 2:
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    break;
  case 3:
    turnOffAllLights();
    clapCount = 0;
    break;
  }
}

void turnOffAllLights()
{
  pinCount = sizeof(ledPins);
  for (int i = 0; i < pinCount; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}
