#include "CppUTest/TestHarness.h"

extern "C"
{
#include "chapter3_led_driver.h"
#include "runtime_error_stub.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
}

static uint16_t virtual_leds;

TEST_GROUP(led_driver_continued){void setup(){

    virtual_leds = 0xFFFF;
led_driver_init(&virtual_leds);
RuntimeErrorStub_Reset();
}

void teardown()
{
    RuntimeErrorStub_Reset();
}
}
;


TEST(led_driver_continued, TurnOnMultipleLeds)
{
    led_turn_on(1);
    led_turn_on(5);
    LONGS_EQUAL(0x11, virtual_leds);
}

TEST(led_driver_continued, TurnOffAnyLed)
{
    led_turn_on(1);
    led_turn_on(5);
    led_turn_off(5);
    LONGS_EQUAL(0x01, virtual_leds);
}

TEST(led_driver_continued, LedMemoryIsNotReadable)
{
    virtual_leds = 0xFFFF;
    led_turn_on(1);
    led_turn_on(5);
    led_turn_off(5);
    LONGS_EQUAL(0x01, virtual_leds);
}

TEST(led_driver_continued, UpperAndLowerBounds)
{
    led_turn_on(1);
    led_turn_on(16);
    LONGS_EQUAL(0x8001, virtual_leds);
}

TEST(led_driver_continued, OutOfBoundsChangesNothing)
{
    led_turn_on(3141);
    led_turn_on(-1);
    LONGS_EQUAL(0, virtual_leds);
}

TEST(led_driver_continued, OutOfBoundsturn_off_ChangesNothing)
{
    led_turn_all_on();
    led_turn_off(3141);
    led_turn_off(-1);
    LONGS_EQUAL(0xFFFF, virtual_leds);
}

TEST(led_driver_continued, OutOfBoundsProducesRuntimeError)
{
    led_turn_on(3141);
    STRCMP_EQUAL("led error: out of bounds", RuntimeErrorStub_GetLastError());
}

TEST(led_driver_continued, OutOfBounds_turnoff_ProducesRuntimeError)
{
    led_turn_off(3141);
    STRCMP_EQUAL("led error: out of bounds", RuntimeErrorStub_GetLastError());
}

TEST(led_driver_continued, IsOn)
{
    led_turn_on(5);
    CHECK_TRUE(led_IsOn(5));
    led_turn_on(6);
    CHECK_TRUE(led_IsOn(6));
}


TEST(led_driver_continued, IsOn_outofbounds)
{
    CHECK_FALSE(led_IsOn(51));
    CHECK_FALSE(led_IsOn(62));
}

TEST(led_driver_continued, IsOff)
{
    led_turn_on(5);
    CHECK_FALSE(led_IsOff(5));
    led_turn_on(4);
    CHECK_FALSE(led_IsOff(4));
}

TEST(led_driver_continued, test_all_outofbounds_on_off)
{
    CHECK_TRUE(led_IsOff(0));
    CHECK_TRUE(led_IsOff(16));
    CHECK_FALSE(led_IsOn(0));
    CHECK_FALSE(led_IsOn(16));
}

TEST(led_driver_continued, TurnOffMultipleLeds)
{
    led_turn_all_on();
    led_turn_off(1);
    led_turn_off(5);
    LONGS_EQUAL(0xFFFF & ~(0x11), virtual_leds);
}

TEST(led_driver_continued, AllOff)
{
    led_turn_all_on();
    led_turn_all_off();
    LONGS_EQUAL(0, virtual_leds);
}