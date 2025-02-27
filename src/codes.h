#ifndef CODES_H
#define CODES_H

// Initializing commands
void handMotorInit();
void yMotorInit();
void zMotorInit();
void bodyMotorInit();

// Sensor commands
float zSensorValue();
float handSensorValue();
void showzSensorValue(float threshold, float period);
void showhandSensorValue(float threshold, float period);

// Motor commands
void moveHandMotor(int time, int speed);
void movezMotor(int time, int speed);
void moveBodyMotor(int time, int speed);
void stepStepper(int step);

// Mission sequence commands
unsigned long grabDomino(float threshold, int speed);
unsigned long lowerArm(float threshold, int speed);

void turnonLED(int pin, int time);
void colorLED(float red, float green, float blue);
void turnoffLED(int pin);
// void moveServo(int angle);
// void servoInit();
// void controlLED();
// void controlServo(float threshold);

#endif
