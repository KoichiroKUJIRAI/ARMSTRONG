#include <Arduino.h>
#include <stepper.h>
#include "codes.h"

// Parameters for controling arm movements
int yMotorStep = 540;
int yMotorTotalStep = 180;
int yMotorSpeed = 100;
int loweringSpeed = 500;
int grabbingVoltage = 3;

// Sensor thresholds
float loweringThreshold = 1;
float grabbingThreshold = 1;

// Length of delay between each commands
int delayTime = 500;

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
  // loweringTime = lowerArm(loweringThreshold, loweringSpeed);
  // delay(delayTime);
  Serial.println("Grabbing");
  grabDomino(grabbingThreshold, grabbingVoltage);
  delay(delayTime);
  // movezMotor(loweringTime, -loweringSpeed);
  // delay(delayTime);
  // step(yMotorStep, yMotorSpeed, yMotorTotalStep);
  // delay(delayTime);
  // loweringTime = lowerArm(loweringThreshold, loweringSpeed);
  // delay(delayTime);
  Serial.print("Opening");
  openingHand(grabbingThreshold, grabbingVoltage);
  delay(delayTime);
  // movezMotor(loweringTime, -loweringSpeed);
  // delay(delayTime);
  // step(-yMotorStep, yMotorSpeed, yMotorTotalStep);
  // delay(delayTime);
  // moveBodyMotor(bodyMovingTime, bodyMovingSpeed);
  // delay(delayTime);
}