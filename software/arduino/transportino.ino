#include "led.h"
#include "motor.h"
#include "defs.h"
#include <SoftwareSerial.h>

SoftwareSerial soft_serial(4, 5);

fade::led* status_led;
actuators::motor* motor_a;
actuators::motor* motor_b;

void onEncAUpdate() 
{
    if(digitalRead(motor_a->pin_enc_a))
    {
        if(!motor_a->enc_b) 
        {
            motor_a->dir = 0;
        }
        motor_a->enc_a = true;
    }  
    
    if(digitalRead(motor_a->pin_enc_b))
    {
        if(!motor_a->enc_a) 
        {
            motor_a->dir = 1;
        }
        motor_a->enc_b = true;
    }

    if(motor_a->enc_a && motor_a->enc_b) 
    {
        motor_a->pulse++;
        motor_a->enc_a = false;
        motor_a->enc_b = false;
    }
}

void onEncBUpdate() 
{
    if(digitalRead(motor_b->pin_enc_a))
    {
        if(!motor_b->enc_b) 
        {
            motor_b->dir = 0;
        }
        motor_b->enc_a = true;
    }  
    
    if(digitalRead(motor_b->pin_enc_b))
    {
        if(!motor_b->enc_a) 
        {
            motor_b->dir = 1;
        }
        motor_b->enc_b = true;
    }

    if(motor_b->enc_a && motor_b->enc_b) 
    {
        motor_b->pulse++;
        motor_b->enc_a = false;
        motor_b->enc_b = false;
    }
}

void setup() 
{

    soft_serial.begin(9600);
    soft_serial.print("Transportino build ");
    soft_serial.print(BUILD_NUMBER);
    soft_serial.print("\nStarting...");

    status_led = fade::createLed(STATUS_LED, 20, 50L);

    motor_a = actuators::init_motor(MOTOR_A0, MOTOR_A1, MOTOR_ENCA0, MOTOR_ENCA1);
    motor_b = actuators::init_motor(MOTOR_B0, MOTOR_B1, MOTOR_ENCB0, MOTOR_ENCB1);
    actuators::set_encoder_interrupts(motor_a, onEncAUpdate);
    actuators::set_encoder_interrupts(motor_b, onEncBUpdate);
    motor_a->serial = &soft_serial;
    motor_b->serial = &soft_serial;

    soft_serial.println("OK!");
}

const int data_size = 3;
uint8_t read_data[data_size];
int data_length;

const int stats_size = 8;
uint8_t stats[stats_size];

void read_serial() 
{
    if(soft_serial.available() > 0) {
        data_length = soft_serial.readBytes(read_data, data_size);
        if(data_length == data_size) {
            if(!bitRead(read_data[0], 0)) {
                if(bitRead(read_data[1], 0)) {
                    actuators::set_move(motor_b, bitRead(read_data[1], 1), read_data[2]);
                } else {
                    actuators::set_move(motor_a, bitRead(read_data[1], 1), read_data[2]);
                }
            }
            else {
                if(bitRead(read_data[2], 0)) {
                    stats[0] = motor_a->desired_rpm;
                    stats[1] = motor_a->actual_rpm;
                    stats[2] = motor_a->dir;
                    stats[3] = motor_a->pwm;
                    stats[4] = motor_b->desired_rpm;
                    stats[5] = motor_b->actual_rpm;
                    stats[6] = motor_b->dir;
                    stats[7] = motor_b->pwm;
                    soft_serial.write(stats, 8);
                }
                else {
                    if(bitRead(read_data[1], 0)) {
                        soft_serial.write(motor_b->actual_rpm);
                    } else {
                        soft_serial.write(motor_a->actual_rpm);
                    }
                }
            }
        }  
    }
}

void loop() 
{
    fade::updateLed(status_led);
    actuators::update_motor(motor_a);
    actuators::update_motor(motor_b);

    read_serial();

}
