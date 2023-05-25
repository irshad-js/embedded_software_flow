#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


int led_driver_init(uint16_t *address);
int led_turn_on(uint16_t led_number);
int led_turn_off(uint16_t led_number);
void led_turn_all_on(void);
void led_turn_all_off(void);
bool led_IsOn(uint16_t led_number);
bool led_IsOff(uint16_t led_number);