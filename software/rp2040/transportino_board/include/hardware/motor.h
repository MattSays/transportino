#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "transportino_error.h"

#define MOTOR_CLOCKWISE 0
#define MOTOR_COUNTERCLOCKWISE 1

typedef struct _motor {
    uint8_t pin_a;
    uint8_t pin_b;

    uint8_t pwm_pin;
    uint8_t pwm_slice;
    uint16_t pwm_value;

    uint8_t enc_pin_a;
    uint8_t enc_pin_b;

    volatile int32_t current_rpm;
    int32_t desired_rpm;  
    uint16_t max_rpm;
    uint16_t pwm_per_rpm;

    void* encoder_timer;

    volatile int32_t pulses;
    volatile bool dir;
} motor;

terror motor_init(motor* motor, uint8_t pin_a, uint8_t pin_b, uint8_t pwm_pin, uint8_t enc_pin_a, uint8_t enc_pin_b, uint16_t max_rpm, void* motordrv);
terror motor_set_dir(motor* motor, bool dir);
terror motor_set_speed(motor* motor, uint16_t rpm);
terror motor_stop(motor* motor);
