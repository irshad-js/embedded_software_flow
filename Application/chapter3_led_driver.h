#include <stdint.h>
#include <stdio.h>

int led_driver_init(uint16_t *address);
int led_turn_on(uint16_t led_number);
int led_turn_off(uint16_t led_number);