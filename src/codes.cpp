#include <Arduino.h>
#include <ESP32Servo.h>
#include <stepper.h>
#include "codes.h"

// Pins for Sensors
#define zSensorPin 34
#define handSensorPin 35

// Pins for Stepping Motor of y-axis conveying
#define yMotorPin1 26
#define yMotorPin2 14
#define yMotorPin3 27
#define yMotorPin4 12

#define LEDredPin 26
#define LEDgreenPin 27
#define LEDbluePin 14

// Pins for DC Motor of z-axis conveying
#define zMotorAnlPin 25
#define zMotorDgtPin1 33
#define zMotorDgtPin2 32

// Pins for DC Motor of hand grabbing and releasing
#define handMotorAnlPin 4
#define handMotorDgtPin1 16
#define handMotorDgtPin2 17

// Pins for DC Motor of body moving
#define bodyMotorAnlPin 5
#define bodyMotorDgtPin1 18
#define bodyMotorDgtPin2 19

// Defining class objects
Stepper myStepper(180, 26, 27, 14, 12);

// Initializing commands
void handMotorInit()
{
    pinMode(handMotorDgtPin1, OUTPUT);
    pinMode(handMotorDgtPin2, OUTPUT);
    digitalWrite(handMotorDgtPin1, LOW);
    digitalWrite(handMotorDgtPin2, LOW);
    analogWrite(handMotorAnlPin, 0);
}

void yMotorInit()
{
    pinMode(yMotorPin1, OUTPUT);
    pinMode(yMotorPin2, OUTPUT);
    pinMode(yMotorPin3, OUTPUT);
    pinMode(yMotorPin4, OUTPUT);
    digitalWrite(yMotorPin1, LOW);
    digitalWrite(yMotorPin2, LOW);
    digitalWrite(yMotorPin3, LOW);
    digitalWrite(yMotorPin4, LOW);
    myStepper.setSpeed(50);
}

void zMotorInit()
{
    pinMode(zMotorDgtPin1, OUTPUT);
    pinMode(zMotorDgtPin2, OUTPUT);
    digitalWrite(zMotorDgtPin1, LOW);
    digitalWrite(zMotorDgtPin2, LOW);
    analogWrite(zMotorAnlPin, 0);
}

void bodyMotorInit()
{
    pinMode(bodyMotorDgtPin1, OUTPUT);
    pinMode(bodyMotorDgtPin2, OUTPUT);
    digitalWrite(bodyMotorDgtPin1, LOW);
    digitalWrite(bodyMotorDgtPin2, LOW);
    analogWrite(bodyMotorAnlPin, 0);
}

// Sensor commands
float zSensorValue()
{
    float sensorvalue = analogRead(zSensorPin);
    return sensorvalue;
}

float handSensorValue()
{
    float sensorvalue = analogRead(handSensorPin);
    return sensorvalue;
}

void showzSensorValue(float threshold, float period)
{
    float sensorvalue = zSensorValue();
    Serial.print(sensorvalue);
    if (sensorvalue <= threshold)
    {
        Serial.println("LOW");
    }
    else
    {
        Serial.println("HIGH");
    }
    delay(period);
}

void showhandSensorValue(float threshold, float period)
{
    float sensorvalue = handSensorValue();
    Serial.print(sensorvalue);
    if (sensorvalue <= threshold)
    {
        Serial.println("LOW");
    }
    else
    {
        Serial.println("HIGH");
    }
    delay(period);
}

// Motor commands
void moveHandMotor(int time, int speed)
{
    analogWrite(handMotorAnlPin, speed);
    if (speed >= 0)
    {
        digitalWrite(handMotorDgtPin1, HIGH);
        digitalWrite(handMotorDgtPin2, LOW);
    }
    else
    {
        digitalWrite(handMotorDgtPin1, LOW);
        digitalWrite(handMotorDgtPin2, HIGH);
    }
    delay(time);
    digitalWrite(zMotorDgtPin1, LOW);
    digitalWrite(zMotorDgtPin2, LOW);
}

void movezMotor(int time, int speed)
{
    analogWrite(zMotorAnlPin, speed);
    if (speed >= 0)
    {
        digitalWrite(zMotorDgtPin1, HIGH);
        digitalWrite(zMotorDgtPin2, LOW);
    }
    else
    {
        digitalWrite(zMotorDgtPin1, LOW);
        digitalWrite(zMotorDgtPin2, HIGH);
    }
    delay(time);
    digitalWrite(zMotorDgtPin1, LOW);
    digitalWrite(zMotorDgtPin2, LOW);
}

void moveBodyMotor(int time, int speed)
{
    analogWrite(bodyMotorAnlPin, speed);
    if (speed >= 0)
    {
        digitalWrite(bodyMotorDgtPin1, HIGH);
        digitalWrite(bodyMotorDgtPin2, LOW);
    }
    else
    {
        digitalWrite(bodyMotorDgtPin1, LOW);
        digitalWrite(bodyMotorDgtPin2, HIGH);
    }
    delay(time);
    digitalWrite(zMotorDgtPin1, LOW);
    digitalWrite(zMotorDgtPin2, LOW);
}

void stepStepper(int step)
{
    myStepper.step(step);
    digitalWrite(yMotorPin1, LOW);
    digitalWrite(yMotorPin2, LOW);
    digitalWrite(yMotorPin3, LOW);
    digitalWrite(yMotorPin4, LOW);
}

void stepMotor(int thisStep)
{
    switch (thisStep)
    {
    case 0: // 1010
        digitalWrite(yMotorPin1, HIGH);
        digitalWrite(yMotorPin2, LOW);
        digitalWrite(yMotorPin3, HIGH);
        digitalWrite(yMotorPin4, LOW);
        break;
    case 1: // 0110
        digitalWrite(yMotorPin1, LOW);
        digitalWrite(yMotorPin2, HIGH);
        digitalWrite(yMotorPin3, HIGH);
        digitalWrite(yMotorPin4, LOW);
        break;
    case 2: // 0101
        digitalWrite(yMotorPin1, LOW);
        digitalWrite(yMotorPin2, HIGH);
        digitalWrite(yMotorPin3, LOW);
        digitalWrite(yMotorPin4, HIGH);
        break;
    case 3: // 1001
        digitalWrite(yMotorPin1, HIGH);
        digitalWrite(yMotorPin2, LOW);
        digitalWrite(yMotorPin3, LOW);
        digitalWrite(yMotorPin4, HIGH);
        break;
    }
}

void step(int steps_to_move, long whatSpeed, int number_of_steps)
{
    int steps_left = abs(steps_to_move); // how many steps to take
    int step_number = 0;
    int direction = 0;
    unsigned long last_step_time = 0;
    unsigned long step_delay = 60L * 1000L * 1000L / number_of_steps / whatSpeed;

    // determine direction based on whether steps_to_mode is + or -:
    if (steps_to_move > 0)
    {
        direction = 1;
    }
    if (steps_to_move < 0)
    {
        direction = 0;
    }
    Serial.print("direction is ");
    if (direction)
    {
        Serial.println("positive");
    }
    else
    {
        Serial.println("negative");
    }
    // decrement the number of steps, moving one step each time:
    while (steps_left > 0)
    {
        unsigned long now = micros();
        // move only if the appropriate delay has passed:
        if (now - last_step_time >= step_delay)
        {
            // get the timeStamp of when you stepped:
            last_step_time = now;
            // increment or decrement the step number,
            // depending on direction:
            if (direction == 1)
            {
                step_number++;
                if (step_number == number_of_steps)
                {
                    step_number = 0;
                }
            }
            else
            {
                if (step_number == 0)
                {
                    step_number = number_of_steps;
                }
                step_number--;
            }
            // decrement the steps left:
            steps_left--;
            // step the motor to step number 0, 1, ..., {3 or 10}
            stepMotor(step_number % 4);
            delay(1);
        }
    }
}

// Mission sequence commands
unsigned long grabDomino(float threshold, int speed)
{
    digitalWrite(handMotorDgtPin1, LOW);
    digitalWrite(handMotorDgtPin2, LOW);
    analogWrite(handMotorAnlPin, speed);
    delay(5);
    unsigned long startTime = millis();
    unsigned long time = millis();
    float pressure = handSensorValue();
    digitalWrite(handMotorDgtPin1, HIGH);
    while (pressure < threshold)
    {
        delay(5);
        unsigned long time = millis();
        pressure = handSensorValue();
    }
    digitalWrite(zMotorDgtPin1, LOW);
    unsigned long grabbingTime = time - startTime;
    return grabbingTime;
}

unsigned long lowerArm(float threshold, int speed)
{
    digitalWrite(zMotorDgtPin1, LOW);
    digitalWrite(zMotorDgtPin2, LOW);
    analogWrite(zMotorAnlPin, speed);
    delay(5);
    unsigned long startTime = millis();
    unsigned long time = millis();
    float pressure = zSensorValue();
    digitalWrite(zMotorDgtPin1, HIGH);
    while (pressure < threshold)
    {
        delay(5);
        unsigned long time = millis();
        pressure = zSensorValue();
        Serial.print("pressure =");
        Serial.println(pressure);
    }
    digitalWrite(zMotorDgtPin1, LOW);
    unsigned long grabbingTime = time - startTime;
    return grabbingTime;
}

void turnonLED(int pin, int time)
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    delay(time);
    digitalWrite(pin, LOW);
    delay(time);
}

void colorLED(float red, float green, float blue)
{
    analogWrite(LEDredPin, (red * 4095) / 256);
    analogWrite(LEDgreenPin, (green * 4095) / 256);
    analogWrite(LEDbluePin, (blue * 4095) / 256);
}

void turnoffLED(int pin)
{
    analogWrite(pin, 0);
}
// もう使わないコードたち
//  Servo handServo;
//  bool servoRunning = false; // サーボが動作中かどうかのフラグ
//  #define SERVO_RUN_TIME_MS 10000 // サーボを回転させる時間（ミリ秒）
//  void servoInit()
//  {
//      handServo.attach(servoPin);
//      handServo.setPeriodHertz(50);
//      handServo.write(0);
//  }
//  void moveServo(int angle)
//  {
//      Serial.print("Moving servo to ");
//      Serial.println(angle);
//      handServo.write(angle);
//  }
//  void controlZDC(float threshold, int speed)
//  {
//      analogWrite(zMotorAnlPin, speed);   // speed=150
//      unsigned long startTime = millis(); // 開始時間を記録
//      while (analogRead(sensorPin) < threshold)
//      {
//          a
//      }
//  }
//  void controlLED()
//  {
//      float inputValue = analogRead(sensorPin);
//      Serial.print(inputValue);
//      if (inputValue >= 2000)
//      {
//          digitalWrite(LEDPin, LOW);
//          Serial.println("HIGH");
//      }
//      else
//      {
//          digitalWrite(LEDPin, HIGH);
//          Serial.println("LOW");
//      }
//      delay(100);
//  }
//  サーボを一定時間回転し続ける
//  void activateServo()
//  {
//      Serial.println("Servo Started!");
//      unsigned long startTime = millis(); // 開始時間を記録
//      while (millis() - startTime < SERVO_RUN_TIME_MS)
//      { // 一定時間動作
//          // 0度 → 180度 へ滑らかに回転
//          for (int angle = 0; angle <= 180; angle++)
//          {
//              myServo.write(angle);
//              delay(20); // 20ms の間隔で少しずつ回転
//              if (millis() - startTime >= SERVO_RUN_TIME_MS)
//                  return; // 時間経過で停止
//          }
//          // 180度 → 0度 へ滑らかに回転
//          for (int angle = 180; angle >= 0; angle--)
//          {
//              myServo.write(angle);
//              delay(20); // 20ms の間隔で少しずつ回転
//              if (millis() - startTime >= SERVO_RUN_TIME_MS)
//                  return; // 時間経過で停止
//          }
//      }
//      Serial.println("Servo Stopped!");
//  }
//  // GPIO33 の入力値を監視し、2000以上ならサーボを一定時間回転させる
//  void checkAndActivateServo()
//  {
//      float inputValue = analogRead(sensorPin);
//      Serial.print("Sensor Value: ");
//      Serial.println(inputValue);
//      if (inputValue >= 2000 && !servoRunning)
//      {
//          servoRunning = true;  // サーボを動作中にする
//          activateServo();      // サーボを動作開始
//          servoRunning = false; // 一定時間後に停止
//      }
//      delay(100); // チラつきを防ぐための短い待機
//  }