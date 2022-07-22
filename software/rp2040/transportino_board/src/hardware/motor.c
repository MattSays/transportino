#include "hardware/motor.h"

#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#include "transportino_config.h"
#include "transportino_board.h"
#include "hardware/motordrv.h"
#include "transportino_error.h"

typedef struct repeating_timer enc_timer;

tboard* _board;
motordrv* _motordrv;

bool motor_on_encoder_check(enc_timer* timer);
void motor_on_encoder_interrupt(uint gpio, uint32_t event_mask);

terror motor_init(motor* motor, uint8_t pin_a, uint8_t pin_b, uint8_t pwm_pin, uint8_t enc_pin_a, uint8_t enc_pin_b, uint16_t max_rpm, void* board)
{
    if(_motordrv == NULL) {
        _board = (tboard*) board;
        _motordrv = _board->motordrv;
    }

    motor->current_rpm = 0;
    motor->pulses = 0;
    motor->desired_rpm = 0;
    motor->pwm_slice = 0;
    motor->pwm_value = 0;
    motor->max_rpm = max_rpm;
    motor->pwm_per_rpm = UINT16_MAX / max_rpm;

    motor->pin_a = pin_a;
    gpio_init(pin_a);
    gpio_set_dir(pin_a, GPIO_OUT);

    motor->pin_b = pin_b;
    gpio_init(pin_b);
    gpio_set_dir(pin_b, GPIO_OUT);

    motor->pwm_pin = pwm_pin;
    gpio_set_function(pwm_pin, GPIO_FUNC_PWM);
    motor->pwm_slice = pwm_gpio_to_slice_num(pwm_pin);
    pwm_config motor_config = pwm_get_default_config();    
    pwm_init(motor->pwm_slice, &motor_config, true);

    motor->current_rpm = 0;

    motor->enc_pin_a = enc_pin_a;
    
    gpio_init(enc_pin_a);
    gpio_set_dir(enc_pin_a, GPIO_IN);
    gpio_pull_up(enc_pin_a);
    gpio_set_irq_enabled_with_callback(enc_pin_a, GPIO_IRQ_EDGE_RISE, true, motor_on_encoder_interrupt);

    motor->enc_pin_b = enc_pin_b;
    gpio_init(enc_pin_b);
    gpio_pull_up(enc_pin_b);
    gpio_set_dir(enc_pin_b, GPIO_IN);

    // Setup timer for encoders.
    motor->encoder_timer = malloc(sizeof(enc_timer));
    if(!add_repeating_timer_ms(1000, motor_on_encoder_check, motor, motor->encoder_timer)) {
        return terror_make(TRANSPORTINO_MOTORDRV, TRANSPORTINO_INIT_ERROR, true);
    }
    
    return NULL_ERROR;
}

bool motor_on_encoder_check(enc_timer* timer) 
{
    motor* _motor = (motor*)timer->user_data;
    _motor->current_rpm = (_motor->pulses / MOTOR_PULSES_PER_REVOLUTIONS);
    _motor->pulses = 0;
    return true;
}

void motor_on_encoder_interrupt(uint gpio, uint32_t event_mask)
{
    motor* motor;
    terror error = motordrv_get_by_enc_pin(_motordrv, gpio, &motor);

    if(!transportino_is_error_null(error)) {
        transportino_error(_board, error);
        return;
    }

    bool enc_b = gpio_get(motor->enc_pin_b);

    if(enc_b) {
        motor->pulses--;
    } else {
        motor->pulses++;
    }

}

terror motor_set_dir(motor* motor, bool dir)
{
    if(motor->dir == dir) {
        return NULL_ERROR;
    }

    motor->dir = dir;

    if(dir == MOTOR_CLOCKWISE) {
        gpio_put(motor->pin_a, 1);
        gpio_put(motor->pin_b, 0);
    } else {
        gpio_put(motor->pin_a, 0);
        gpio_put(motor->pin_b, 1);
    }

    return NULL_ERROR;
}


terror motor_set_speed(motor* motor, uint16_t rpm)
{
    if(motor->desired_rpm == rpm) {
        return NULL_ERROR;
    }

    if(rpm > motor->max_rpm) {
        return motor_set_speed(motor, motor->max_rpm);
    }

    motor->desired_rpm = rpm;
    motor->pwm_value = (rpm * motor->pwm_per_rpm);
    pwm_set_gpio_level(motor->pwm_pin, motor->pwm_value);

    return NULL_ERROR;
}

terror motor_stop(motor* motor)
{
    motor->desired_rpm = 0;
    motor->pwm_value = 0;
    pwm_set_gpio_level(motor->pwm_pin, 0);
    gpio_put(motor->pin_a, 0);
    gpio_put(motor->pin_b, 0);    

    return NULL_ERROR;
}