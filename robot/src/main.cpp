#include <Arduino.h>
#include "MotorDC.h"
#include "Servo.h"

#define PIN_LEFT_DIR1  7//in1
#define PIN_LEFT_DIR2  8//in2
#define PIN_LEFT_EN    6//ena
#define PIN_RIGHT_DIR1 2//in3
#define PIN_RIGHT_DIR2 4//in4
#define PIN_RIGHT_EN   5//enb
#define PIN_SERVO1     10
#define PIN_SERVO2     11

MotorDC leftWheel;
MotorDC rightWheel;
Servo servo1;
Servo servo2;
int pos_servo1 = 0;
int pos_servo2 = 0;

void increment(Servo servo, int step){
  int val = servo.read() + step;
  servo.write(val);
  delay(10);  
}

void decrement(Servo servo, int step){
  int val = servo.read() - step;
  servo.write(val);
  delay(10);  
}

void testServo(){
  for (int i = 0; i <= 180; i += 1) { 
    increment(servo1,1); 
    increment(servo2,1);
  }
  for (int i = 0; i <= 180; i += 1) { 
    decrement(servo1,1); 
    decrement(servo2,1);                 
  }
}

void testMotor(){
  for (int i = 0; i <= 255; i += 1) { 
    leftWheel.setSpeed(i, FORWARD);              
    rightWheel.setSpeed(i, FORWARD);
    delay(5);
  }
  leftWheel.stop();              
  rightWheel.stop();
  delay(100);
  for (int i = 0; i <= 255; i += 1) { 
    leftWheel.setSpeed(i, BACKWARDS);              
    rightWheel.setSpeed(i, BACKWARDS);
    delay(5);
  }
  leftWheel.stop();              
  rightWheel.stop();
  delay(100);
}

void forward(){
  leftWheel.setSpeed(255, FORWARD);
  rightWheel.setSpeed(255, FORWARD);
}

void setup() {
  Serial.begin(115200);
  leftWheel.init(PIN_LEFT_DIR1, PIN_LEFT_DIR2, PIN_LEFT_EN);
  rightWheel.init(PIN_RIGHT_DIR1, PIN_RIGHT_DIR2, PIN_RIGHT_EN);
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
}

void loop() {
  forward();
}