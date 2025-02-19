#include <Arduino.h>
#include <ESP32Servo.h>
#include <stepper.h>
#include "codes.h"

// #define SERVO_RUN_TIME_MS 10000 // サーボを回転させる時間（ミリ秒）
#define sensorPin 35
#define yMotorPin1 26
#define yMotorPin2 27
#define yMotorPin3 14
#define yMotorPin4 12
#define zMotorAnlPin 25
#define zMotorDgtPin1 33
#define zMotorDgtPin2 32
#define LEDPin 13

Stepper myStepper(180, 26, 27, 14, 12);
Servo myServo;
// bool servoRunning = false; // サーボが動作中かどうかのフラグ

void pinSetup()
{
    // myServo.attach(servoPin);
    pinMode(yMotorPin1, OUTPUT);
    pinMode(yMotorPin2, OUTPUT);
    pinMode(yMotorPin3, OUTPUT);
    pinMode(yMotorPin4, OUTPUT);
    pinMode(zMotorDgtPin1, OUTPUT);
    pinMode(zMotorDgtPin2, OUTPUT);
    pinMode(LEDPin, OUTPUT);
    myStepper.setSpeed(50);
}

void positiveMovezDC(float time, float speed)
{
    analogWrite(zMotorAnlPin, speed);
    digitalWrite(zMotorDgtPin1, HIGH);
    digitalWrite(zMotorDgtPin2, LOW);
    delay(time);
    digitalWrite(zMotorDgtPin1, LOW);
    digitalWrite(zMotorDgtPin2, LOW);
}

void negativeMovezDC(float time, float speed)
{
    analogWrite(zMotorAnlPin, speed);
    digitalWrite(zMotorDgtPin1, LOW);
    digitalWrite(zMotorDgtPin2, HIGH);
    delay(time);
    digitalWrite(zMotorDgtPin1, LOW);
    digitalWrite(zMotorDgtPin2, LOW);
}

void stepStepper(int step)
{
    myStepper.step(step);
    delay(100);
    digitalWrite(yMotorPin1, LOW);
    digitalWrite(yMotorPin2, LOW);
    digitalWrite(yMotorPin3, LOW);
    digitalWrite(yMotorPin4, LOW);
}

// void controlZDC(float threshold, int speed)
// {
//     analogWrite(zMotorAnlPin, speed);   // speed=150
//     unsigned long startTime = millis(); // 開始時間を記録
//     while (analogRead(sensorPin) < threshold)
//     {
//         a
//     }
// }

void showValue()
{
    float inputValue = analogRead(sensorPin);
    Serial.print("value = ");
    Serial.println(inputValue);
    delay(50);
}

void showValueAndStatus()
{
    float inputValue = analogRead(sensorPin);
    Serial.print(inputValue);
    if (inputValue <= 2000)
    {
        Serial.println("LOW");
    }
    else
    {
        Serial.println("HIGH");
    }
    delay(50);
}

void controlLED()
{
    float inputValue = analogRead(sensorPin);
    Serial.print(inputValue);
    if (inputValue >= 2000)
    {
        digitalWrite(LEDPin, LOW);
        Serial.println("HIGH");
    }
    else
    {
        digitalWrite(LEDPin, HIGH);
        Serial.println("LOW");
    }
    delay(100);
}

void controlServo()
{
    float inputValue = analogRead(sensorPin);
    Serial.print(inputValue);
    unsigned long startTime = millis();
    if (inputValue >= 100)
    {
        Serial.println("HIGH");
        myServo.write(50);
    }
    else
    {
        Serial.println("LOW");
        myServo.write(90);
    }
    delay(100);
}
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

// サーボを一定時間回転し続ける
// void activateServo()
// {
//     Serial.println("Servo Started!");

//     unsigned long startTime = millis(); // 開始時間を記録

//     while (millis() - startTime < SERVO_RUN_TIME_MS)
//     { // 一定時間動作
//         // 0度 → 180度 へ滑らかに回転
//         for (int angle = 0; angle <= 180; angle++)
//         {
//             myServo.write(angle);
//             delay(20); // 20ms の間隔で少しずつ回転

//             if (millis() - startTime >= SERVO_RUN_TIME_MS)
//                 return; // 時間経過で停止
//         }

//         // 180度 → 0度 へ滑らかに回転
//         for (int angle = 180; angle >= 0; angle--)
//         {
//             myServo.write(angle);
//             delay(20); // 20ms の間隔で少しずつ回転

//             if (millis() - startTime >= SERVO_RUN_TIME_MS)
//                 return; // 時間経過で停止
//         }
//     }

//     Serial.println("Servo Stopped!");
// }

// // GPIO33 の入力値を監視し、2000以上ならサーボを一定時間回転させる
// void checkAndActivateServo()
// {
//     float inputValue = analogRead(sensorPin);
//     Serial.print("Sensor Value: ");
//     Serial.println(inputValue);

//     if (inputValue >= 2000 && !servoRunning)
//     {
//         servoRunning = true;  // サーボを動作中にする
//         activateServo();      // サーボを動作開始
//         servoRunning = false; // 一定時間後に停止
//     }

//     delay(100); // チラつきを防ぐための短い待機
// }
