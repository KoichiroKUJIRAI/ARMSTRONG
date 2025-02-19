#include <Arduino.h>
#include <ESP32Servo.h>
#include <stepper.h>
#include "codes.h"

void setup()
{
  Serial.begin(115200);
  pinSetup();
}

void loop()
{
  stepStepper(-180);
  delay(100);
}