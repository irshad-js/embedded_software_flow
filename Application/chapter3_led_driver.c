#include "chapter3_led_driver.h"

static uint16_t *led_address;

int led_driver_init(uint16_t *address)
{
    led_address = address;
    *led_address = 0;
}

int led_turn_on(uint16_t led_number)
{
    *led_address = 1;
}

int led_turn_off(uint16_t led_number)
{
    *led_address = 0;
}