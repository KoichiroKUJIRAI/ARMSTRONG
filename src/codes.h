#ifndef CODES_H
#define CODES_H

void pinSetup();
void showValue();
void showValueAndStatus();
void controlLED();
void turnonLED();
void controlServo();
void positiveMovezDC(float time, float speed);
void negativeMovezDC(float time, float speed);
void stepStepper(int step);

#endif
