#include "MotorDC.h"

MotorDC::MotorDC()
{
    
}

MotorDC::~MotorDC()
{
    Serial.println("generic destructor");
}

void MotorDC::init(uint8_t dir_1, uint8_t dir_2)
{
    controlType = PULSE_INPUTS;
    pins.dir_1 = dir_1;
    pins.dir_2 = dir_2;
    pinMode(pins.dir_1, OUTPUT);
    pinMode(pins.dir_2, OUTPUT);
    //setMap(MIN_INPUT, MAX_INPUT, MIN_MAP_5206, FAST_MAP_5206);
}

void MotorDC::init(uint8_t dir_1, uint8_t dir_2, uint8_t enable)
{
    controlType = PULSE_ENABLE;
    pins.dir_1 = dir_1;
    pins.dir_2 = dir_2;
    pins.enable = enable;
    pinMode(pins.dir_1, OUTPUT);
    pinMode(pins.dir_2, OUTPUT);
    pinMode(pins.enable, OUTPUT);
    // setMap(MIN_INPUT, MAX_INPUT, MIN_MAP_L298, FAST_MAP_L298);
}

void MotorDC::setSpeed(int speed, Direction dir)
{
    // 2 wire
    if(speed == 0)
    {
        stop();
        return;
    }
    int pwm = calculatePWM(speed);
    if (dir == FORWARD)
    {
        if(controlType == PULSE_INPUTS){
            digitalWrite(pins.dir_2, LOW);
            analogWrite(pins.dir_1, pwm);
        }
        else {
            digitalWrite(pins.dir_1, HIGH);
            digitalWrite(pins.dir_2, LOW);
            analogWrite(pins.enable, pwm);
        }
    }
    else if (dir == BACKWARDS)
    {
        if(controlType == PULSE_INPUTS){
            digitalWrite(pins.dir_1, LOW);
            analogWrite(pins.dir_2, pwm);
        }
        else {
            digitalWrite(pins.dir_1, LOW);
            digitalWrite(pins.dir_2, HIGH);
            analogWrite(pins.enable, pwm);
        }
    }
}

void MotorDC::stop()
{
    digitalWrite(pins.dir_1, LOW);
    digitalWrite(pins.dir_2, LOW);
    if(controlType == PULSE_ENABLE){
         digitalWrite(pins.enable, LOW);
    }
}

int MotorDC::calculatePWM(int p_speed)
{
   // return map(abs(p_speed), min_input, max_input, min_mapped, max_mapped);
    return p_speed;
}

void MotorDC::setMap(int p_min_input, int p_max_input, int p_min_mapped, int p_max_mapped)
{
    min_input = p_min_input;
    max_input = p_max_input;
    min_mapped = p_min_mapped;
    max_mapped = p_max_mapped;
}