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
float openingSensorValue();
void showzSensorValue(float threshold, float period);
void showhandSensorValue(float threshold, float period);
void showOpeningSensorValue(float threshold, float period);

// Motor commands
void moveHandMotor(int time, float voltage);
void movezMotor(int time, int speed);
void moveBodyMotor(int time, int speed);
void stepStepper(int step);
void stepMotor(int thisStep);
void step(int steps_to_move, long whatSpeed, int number_of_steps);

// Mission sequence commands
void grabDomino(float threshold, float voltage);
void openingHand(float threshold, float voltage);
unsigned long lowerArm(float threshold, int speed);

void turnonLED(int pin, int time);
void colorLED(float red, float green, float blue);
void turnoffLED(int pin);
// void moveServo(int angle);
// void servoInit();
// void controlLED();
// void controlServo(float threshold);

#endif
