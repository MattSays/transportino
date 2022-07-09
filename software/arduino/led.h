
namespace fade
{
    typedef struct _led
    {
        int reverting;
        int pin;
        int step;
        int max_step;
        int value;
        int value_increase;
        long last_time;
        long step_time;
    } led;

    led* createLed(int led_pin, int value_increase, long step_time);
    void resetLed(led* led);
    void setLed(led* led, int value_increase, long step_time);
    void updateLed(led* led);
    void deleteLed(led* led);
} // namespace fade

 // namespace FadeLED
