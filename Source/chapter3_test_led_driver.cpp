#include "CppUTest/TestHarness.h"

extern "C"
{
#include "chapter3_led_driver.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
}

TEST_GROUP(led_driver){void setup(){}

                       void teardown(){}};

TEST(led_driver, Test_led_driver_initialization)
{
    uint16_t address = 0xFFFF;
    led_driver_init(&address);
    LONGS_EQUAL(0, address);
}

TEST(led_driver, Test_single_led_turn_on)
{
    uint16_t address = 0xFFFF;
    led_driver_init(&address);
    led_turn_on(1);
    LONGS_EQUAL(1, address);
}

TEST(led_driver, Test_single_led_turn_off)
{
    uint16_t address = 0xFFFF;
    led_driver_init(&address);
    led_turn_on(1);
    led_turn_off(1);
    LONGS_EQUAL(0, address);
}