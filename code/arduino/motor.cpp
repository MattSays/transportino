#include "defs.h"
#include "motor.h"
#include <Arduino.h>



actuators::motor* actuators::init_motor(char pin_a, char pin_b, char pin_enc_a, char pin_enc_b)
{
    actuators::motor* motor = new actuators::motor();
    motor->actual_rpm = 0;
    motor->desired_rpm = 0;
    motor->dir = 0;
    motor->enc_a = 0;
    motor->enc_b = 0;
    motor->last_measure = 0;
    
    motor->pin_a = pin_a;
    motor->pin_b = pin_b;
    motor->pin_enc_a = pin_enc_a;
    motor->pin_enc_b = pin_enc_b;

    motor->pulse = 0;

    pinMode(motor->pin_a, OUTPUT);
    pinMode(motor->pin_b, OUTPUT);

    pinMode(pin_enc_a, INPUT);
    pinMode(pin_enc_b, INPUT);

    return motor;
}

void actuators::set_encoder_interrupts(actuators::motor* motor, void (*encoder_func)(void))
{
    attachInterrupt(digitalPinToInterrupt(motor->pin_enc_a), encoder_func, RISING);
    attachInterrupt(digitalPinToInterrupt(motor->pin_enc_b), encoder_func, RISING);
}

void actuators::update_motor(actuators::motor* motor) 
{
    if((millis() - motor->last_measure) >= 1000)
    {
        motor->last_measure = millis();
        motor->actual_rpm = round(((motor->pulse / MOTOR_PPR) * 60.0f) / MOTOR_REDUCTION_RATE);
        motor->pulse = 0;
    }
}

void actuators::set_move(actuators::motor* motor, bool dir, int rpm)
{
    motor->desired_rpm = rpm;
    motor->pwm = round((rpm * 255.0f) / MOTOR_MAX_RPM * 1.0f);
    motor->dir = dir;

    motor->enc_a = false;
    motor->enc_b = false;

    if(dir) 
    {
        analogWrite(motor->pin_a, motor->pwm);
        analogWrite(motor->pin_b, 0);
    }
    else 
    {
        analogWrite(motor->pin_a, 0);
        analogWrite(motor->pin_b, motor->pwm);
    }
    

}

