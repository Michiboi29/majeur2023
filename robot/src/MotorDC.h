#ifndef __MOTOR_DC_H__
#define __MOTOR_DC_H__

#include <stdint.h>
#include "Arduino.h"

#define FREQ            30000
#define RESOLUTION      8
#define MIN_INPUT       0
#define MAX_INPUT       128
#define MIN_MAP_L298    85
#define MIN_MAP_5206    0
#define FAST_MAP_L298   255
#define SLOW_MAP_L298   170
#define FAST_MAP_5206   255
#define SLOW_MAP_5206   128

struct MotorPins
{
    uint8_t dir_1;
    uint8_t dir_2;
    uint8_t channel;
    uint8_t enable;
};
enum MotorControlType {PULSE_ENABLE, PULSE_INPUTS};
enum Direction : bool{FORWARD, BACKWARDS};

class MotorDC{
    public:
        MotorDC();
        void init(uint8_t dir_1, uint8_t dir_2);
        void init(uint8_t dir_1, uint8_t dir_2, uint8_t enable);
        virtual ~MotorDC();
        void setMap(int p_min_input, int p_max_input, int p_min_mapped, int p_max_mapped);
        void setSpeed(int speed, Direction dir);
        void stop();
        MotorPins pins;
    private:
        int calculatePWM(int p_speed);
        MotorControlType controlType;
    protected:
        int min_input = MIN_INPUT;
        int max_input = MAX_INPUT;
        int min_mapped = MIN_INPUT;
        int max_mapped = MAX_INPUT;
};

#endif //__MOTOR_DC_H__