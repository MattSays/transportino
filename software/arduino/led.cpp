#include "led.h"
#include <math.h>
#include <Arduino.h>

fade::led* fade::createLed(int led_pin, int value_increase, long step_time) 
{
    fade::led* led = new fade::led();

    led->pin = led_pin;
    led->value = 0;
    led->step = 0;

    float steps = 255.0f / value_increase;
    led->max_step = round(steps);
    led->value_increase = value_increase;
    led->step_time = step_time;
    led->last_time = 0L;

    pinMode(led_pin, OUTPUT);

    return led; 
}

void fade::resetLed(fade::led* led) 
{
    led->reverting = false;
    led->value = 0;
    led->step = 0;
    led->last_time = 0L;
}

void fade::setLed(fade::led* led, int value_increase, long step_time) 
{
    fade::resetLed(led);
    float steps = 255.0f / value_increase;
    led->max_step = round(steps);
    led->value_increase = value_increase;
    led->step_time = step_time;
}

void fade::updateLed(fade::led* led) 
{   

    if(millis() - led->last_time < led->step_time) 
    {
        return;
    }

    if(led->step >= led->max_step) 
    {
        led->reverting = true;
    } 
    else if(led->step == 0) 
    {
        led->reverting = false;
    }

    if(led->reverting) 
    {
        led->value = max(led->value - led->value_increase, 0);
        led->step--;
    }
    else 
    {
        led->value = min(led->value + led->value_increase, 255);
        led->step++;
    }
    
    analogWrite(led->pin, led->value);
    led->last_time = millis();
}

void fade::deleteLed(fade::led* led) {
    delete led;
}