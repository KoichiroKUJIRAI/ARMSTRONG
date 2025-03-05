#include <Arduino.h>
#include <ESP32Servo.h>
#include <stepper.h>
#include "codes.h"

// Parameters for controling arm movements
int yMotorStep = 540;
int yMotorTotalStep = 180;
int yMotorSpeed = 100;
int loweringSpeed = 500;
int grabbingVoltage = 5;

// Sensor thresholds
float loweringThreshold = 100;
float grabbingThreshold = 50;

// Length of delay between each commands
int delayTime = 300;

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
  movezMotor(200, 3700);
  delay(delayTime);
  // moveHandMotor(500, grabbingSpeed);
  // delay(delayTime);
  // moveHandMotor(500, -grabbingSpeed);
  // delay(delayTime);
  // loweringTime = lowerArm(loweringThreshold, loweringSpeed);
  // delay(delayTime);
  // grabbingTime = grabDomino(grabbingThreshold, grabbingSpeed);
  // delay(delayTime);
  // movezMotor(loweringTime, -loweringSpeed);
  // delay(delayTime);
  // step(yMotorStep, yMotorSpeed, yMotorTotalStep);
  // delay(delayTime);
  // loweringTime = lowerArm(loweringThreshold, loweringSpeed);
  // delay(delayTime);
  // moveHandMotor(grabbingTime, -grabbingSpeed);
  // delay(delayTime);
  // movezMotor(loweringTime, -loweringSpeed);
  // delay(delayTime);
  // step(-yMotorStep, yMotorSpeed, yMotorTotalStep);
  // delay(delayTime);
  // moveBodyMotor(bodyMovingTime, bodyMovingSpeed);
  // delay(delayTime);
}