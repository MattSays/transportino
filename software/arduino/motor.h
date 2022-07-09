#include <SoftwareSerial.h>

namespace actuators
{
    typedef struct _motor {
    char pin_a;
    char pin_b;

    char pin_enc_a;
    char pin_enc_b;

    long last_measure;

    volatile int pulse;
    volatile bool enc_a, enc_b, dir;  

    int actual_rpm, desired_rpm, pwm;

    SoftwareSerial* serial;

    } motor;
    
    motor* init_motor(char pin_a, char pin_b, char pin_enc_a, char pin_enc_b);
    void set_encoder_interrupts(motor* motor, void (*encoder_func)(void));
    void update_motor(motor* motor);

    void set_move(motor* motor, bool dir, int rpm);

} // namespace actuators

