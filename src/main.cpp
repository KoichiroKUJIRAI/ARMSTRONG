#include <Arduino.h>
#include <ESP32Servo.h>
#include <stepper.h>
#include "codes.h"

// Parameters for controling arm movements
int yMotorStep = 540;
int loweringSpeed = 500;
int grabbingSpeed = 500;

// Sensor thresholds
float loweringThreshold = 100;
float grabbingThreshold = 100;

// Length of delay between each commands
int delayTime = 10;

// Parameters for controlling body movement
int bodyMovingSpeed = 100;
int bodyMovingTime = 100;

void setup()
{
  Serial.begin(115200);
  handMotorInit();
  yMotorInit();
  zMotorInit();
  bodyMotorInit();
}

unsigned long loweringTime = 0;
unsigned long grabbingTime = 0;

void loop()
{
  step(180, 50, 180);
  delay(200);
  // loweringTime = lowerArm(loweringThreshold, loweringSpeed);
  // delay(delayTime);
  // grabbingTime = grabDomino(grabbingThreshold, grabbingSpeed);
  // delay(delayTime);
  // movezMotor(loweringTime, -loweringSpeed);
  // delay(delayTime);
  // stepStepper(yMotorStep);
  // delay(delayTime);
  // loweringTime = lowerArm(loweringThreshold, loweringSpeed);
  // delay(delayTime);
  // moveHandMotor(grabbingTime, -grabbingSpeed);
  // delay(delayTime);
  // movezMotor(loweringTime, -loweringSpeed);
  // delay(delayTime);
  // stepStepper(-yMotorStep);
  // delay(delayTime);
  // moveBodyMotor(bodyMovingTime, bodyMovingSpeed);
  // delay(delayTime);
}