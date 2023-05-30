#include "CppUTest/TestHarness.h"

extern "C"
{
#include "FakeTimeService.h"
#include "chapter8_lightscheduler.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
}

static int callback_called;
void callback_alarm(void)
{
    callback_called = 1;
}
TEST_GROUP(FakeTimeService){
    void setup(){} void teardown(){}};


TEST(FakeTimeService, Create)
{
    custom_time_t time;
    TimeService_Create();
    LONGS_EQUAL(TIME_UNKOWN, FakeTimeService_GetDay());
    LONGS_EQUAL(TIME_UNKOWN, FakeTimeService_GetMinute());
}

TEST(FakeTimeService, Set)
{
    custom_time_t time;
    TimeService_Create();
    FakeTimeService_SetMinute(1199);
    FakeTimeService_SetDay(Tuesday);
    //LONGS_EQUAL(Tuesday, FakeTimeService_GetDay());
    //LONGS_EQUAL(1199, FakeTimeService_GetMinute());
    TimeService_GetTime(&time);
    LONGS_EQUAL(1199, time.minute_of_day);
    LONGS_EQUAL(Tuesday, time.day);
}

TEST(FakeTimeService, CallbackSuccess)
{
    callback_called = 0;
    custom_time_t time;
    TimeService_Create();
    TimeService_CreateAlarm(60, callback_alarm);
    FakeTimeService_SetMinute(1199);
    FakeTimeService_SetDay(Tuesday);
    FakeTimeService_OneMinuteIsComplete();
    LONGS_EQUAL(1, callback_called);
}