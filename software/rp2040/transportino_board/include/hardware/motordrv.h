#pragma once

#include <stdbool.h>
#include <stdio.h>

#include "transportino_error.h"
#include "hardware/motor.h"

#include "transportino_config.h"

typedef struct _motordrv {
    uint8_t enable_pin;
    bool power;

    motor motors[MOTORS_NUM];
} motordrv;

typedef struct _motorcfg {
    uint8_t pin_a;
    uint8_t pin_b;

    uint8_t pwm_pin;

    uint8_t enc_pin_a;
    uint8_t enc_pin_b;

    uint16_t max_rpm;
} motorcfg;

terror motordrv_init(motordrv* motordrv, uint8_t enable_pin, motorcfg motors[], void* tboard);
terror motordrv_power(motordrv* motordrv, bool power);
terror motordrv_get(motordrv* motordrv, uint8_t motor_index, motor** motor);
terror motordrv_get_by_enc_pin(motordrv* motordrv, uint8_t enc_pin, motor** mtr);
