#include "chapter3_led_driver.h"
#include "runtime_error.h"
#include <stdbool.h>

static uint16_t *led_address;
static uint16_t led_buffer_image;

int led_driver_init(uint16_t *address)
{
    led_address = address;
    led_buffer_image = 0;
    *led_address = led_buffer_image;
}

int led_turn_on(uint16_t led_number)
{
    if (led_number < 0 || led_number > 16)
    {
        RUNTIME_ERROR("led error: out of bounds", led_number);
        return 0;
    }
    led_buffer_image |= 1 << (led_number - 1);
    *led_address = led_buffer_image;
}

int led_turn_off(uint16_t led_number)
{
    if (led_number < 0 || led_number > 16)
    {
        RUNTIME_ERROR("led error: out of bounds", led_number);
        return 0;
    }
    led_buffer_image &= ~(1 << (led_number - 1));
    *led_address = led_buffer_image;
}

void led_turn_all_on(void)
{
    led_buffer_image = 0xFFFF;
    *led_address = led_buffer_image;
}

bool led_IsOn(uint16_t led_number)
{
    if (led_number < 0 || led_number > 16)
    {
        RUNTIME_ERROR("led error: out of bounds", led_number);
        return false;
    }
    return led_buffer_image & (1 << (led_number - 1));
}

bool led_IsOff(uint16_t led_number)
{
    if (led_number < 0 || led_number > 16)
    {
        RUNTIME_ERROR("led error: out of bounds", led_number);
        return false;
    }
    return !(led_buffer_image & (1 << (led_number - 1)));
}

void led_turn_all_off(void)
{
    led_buffer_image = 0;
    *led_address = led_buffer_image;
}