#include "CppUTest/TestHarness.h"

/*

Time is wrong, day is wrong, no lights are changed
Day is wrong, time is right, no lights are changed
Day is right, time is right, the right light is turned on
Day is right, time is right, the right light is turned off
Schedule every day
Schedule a specific day
Schedule all weekdays
Schedule weekend days
Remove scheduled event
Remove non-existent event
Multiple scheduled events at the same time
Multiple scheduled events for the same light
Remove non scheduled light schedule
Schedule the maximum supported number of events (128)
Schedule too many events

*/
extern "C"
{
#include "FakeTimeService.h"
#include "Fakerandom_minute.h"
#include "LightControllerSpy.h"
#include "RandomMinute.h"
#include "chapter8_lightscheduler.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
}

TEST_GROUP(light_scheduler_tests){
    void setup(){LightController_Create();
LightScheduler_Create();
}

void teardown()
{
}
}
;

TEST(light_scheduler_tests, EverydayScheduledButNotTimeYet)
{
    LightScheduler_turnOn(3, Everyday, 1200);
    FakeTimeService_SetDay(Monday);
    FakeTimeService_SetMinute(1199);
    LightScheduler_wakeup();
    LONGS_EQUAL(LightId_unknown,
                LightControllerSpy_GetLastId());
    LONGS_EQUAL(LightState_unknown,
                LightControllerSpy_GetLastState());
}

TEST(light_scheduler_tests, UnchangedDataDuringInit)
{
    LONGS_EQUAL(LightId_unknown,
                LightControllerSpy_GetLastId());
    LONGS_EQUAL(LightState_unknown,
                LightControllerSpy_GetLastState());
}

TEST(light_scheduler_tests, NoScheduleNothingHappens)
{
    LightScheduler_wakeup();
    LONGS_EQUAL(LightId_unknown,
                LightControllerSpy_GetLastId());
    LONGS_EQUAL(LightState_unknown,
                LightControllerSpy_GetLastState());
}

TEST(light_scheduler_tests, ScheduleOnEverydayNotTimeYet)
{
    LightScheduler_turnOn(2, Everyday, 1200);
    FakeTimeService_SetDay(Monday);
    FakeTimeService_SetMinute(1202);
    LightScheduler_wakeup();
    LONGS_EQUAL(LightId_unknown,
                LightControllerSpy_GetLastId());
    LONGS_EQUAL(LightState_unknown,
                LightControllerSpy_GetLastState());
}

TEST(light_scheduler_tests, ScheduleOnEverydayItsTime)
{
    LightScheduler_turnOn(2, Everyday, 1202);
    FakeTimeService_SetDay(Monday);
    FakeTimeService_SetMinute(1202);
    LightScheduler_wakeup();
    LONGS_EQUAL(2, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON,
                LightControllerSpy_GetLastState());
}

TEST(light_scheduler_tests, ScheduleOffEverydayItsTime)
{
    LightScheduler_turnOff(2, Everyday, 1202);
    FakeTimeService_SetDay(Monday);
    FakeTimeService_SetMinute(1202);
    LightScheduler_wakeup();
    LONGS_EQUAL(2, LightControllerSpy_GetLastId());
    LONGS_EQUAL(LIGHT_OFF,
                LightControllerSpy_GetLastState());
}

static void set_time(int day, int minute)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minute);
}

static void check_lights(int id, int state)
{
    LONGS_EQUAL(id, LightControllerSpy_GetLastId());
    LONGS_EQUAL(state, LightControllerSpy_GetLastState());
}
TEST(light_scheduler_tests, ScheduleWeekEndItsMonday)
{
    LightScheduler_turnOff(2, Weekend, 1200);
    set_time(Monday, 1200);
    LightScheduler_wakeup();
    check_lights(LightId_unknown, LightState_unknown);
}

TEST(light_scheduler_tests, ScheduleWeekEndItsSaturday)
{
    LightScheduler_turnOff(2, Weekend, 1200);
    set_time(Saturday, 1200);
    LightScheduler_wakeup();
    check_lights(2, LIGHT_OFF);
}
TEST(light_scheduler_tests, ScheduleWeekdayItsSaturday)
{
    LightScheduler_turnOff(2, Weekday, 1200);
    set_time(Saturday, 1200);
    LightScheduler_wakeup();
    check_lights(LightId_unknown, LightState_unknown);
}

TEST(light_scheduler_tests, ScheduleWeekdayItsMonday)
{
    LightScheduler_turnOff(2, Weekday, 1200);
    set_time(Monday, 1200);
    LightScheduler_wakeup();
    check_lights(2, LIGHT_OFF);
}

TEST(light_scheduler_tests,
     ScheduleMultipleEventsAtSameTime)
{
    LightScheduler_turnOn(2, Monday, 1200);
    LightScheduler_turnOn(3, Monday, 1200);
    LightScheduler_turnOff(11, Monday, 1200);
    LightScheduler_turnOff(12, Monday, 1200);
    set_time(Monday, 1200);
    LightScheduler_wakeup();
    LONGS_EQUAL(LIGHT_ON,
                LightControllerSpy_GetLastLightState(2));
    LONGS_EQUAL(LIGHT_ON,
                LightControllerSpy_GetLastLightState(3));
    LONGS_EQUAL(LIGHT_OFF,
                LightControllerSpy_GetLastLightState(11));
    LONGS_EQUAL(LIGHT_OFF,
                LightControllerSpy_GetLastLightState(12));
}

TEST_GROUP(lightscheduler_isolated_test){

};

TEST(lightscheduler_isolated_test, Init_and_callback_setup)
{
    LightScheduler_Create();
    POINTERS_EQUAL((void *)LightScheduler_wakeup,
                   (void *)FakeTimeService_GetCallback());
}

TEST(lightscheduler_isolated_test, clean_exit)
{
    LightScheduler_Create();
    LightScheduler_Destroy();
    POINTERS_EQUAL(NULL,
                   (void *)FakeTimeService_GetCallback());
}

TEST(light_scheduler_tests, RejectsTooManyEvents)
{
    for (int tem = 0; tem < 128; tem++)
    {
        LONGS_EQUAL(
            0,
            LightScheduler_turnOn(2, Monday, 100 + tem));
    }
    LONGS_EQUAL(
        -1,
        LightScheduler_turnOn(2, Monday, 100 + 129));
}

TEST(light_scheduler_tests, RemoveScheduledEvent)
{
    LightScheduler_turnOn(2, Monday, 100);
    LightScheduler_turnOn(3, Monday, 100);
    LightScheduler_turnOn(4, Monday, 100);
    LightScheduler_scheduleRemove(2, Monday, 100);
    LightScheduler_scheduleRemove(4, Monday, 100);
    set_time(Monday, 100);
    LightScheduler_wakeup();
    LONGS_EQUAL(-1,
                LightControllerSpy_GetLastLightState(2));
    LONGS_EQUAL(1, LightControllerSpy_GetLastLightState(3));
    LONGS_EQUAL(-1,
                LightControllerSpy_GetLastLightState(4));
}

TEST(light_scheduler_tests, RemoveRecyclesSlot)
{
    for (int tem = 0; tem < 128; tem++)
    {
        LONGS_EQUAL(
            0,
            LightScheduler_turnOn(2, Monday, 100 + tem));
    }
    LightScheduler_scheduleRemove(2, Monday, 100 + 105);
    LONGS_EQUAL(
        0,
        LightScheduler_turnOn(4, Monday, 100 + 105));
    LONGS_EQUAL(
        -1,
        LightScheduler_turnOn(4, Monday, 100 + 106));
}

TEST(light_scheduler_tests, AcceptValidLightIds)
{
    LONGS_EQUAL(0,
                LightScheduler_turnOn(0, Monday, 100 + 2));
    LONGS_EQUAL(0,
                LightScheduler_turnOn(15, Monday, 100 + 3));
    LONGS_EQUAL(0,
                LightScheduler_turnOn(31, Monday, 100 + 4));
}

TEST(light_scheduler_tests, RejectInValidLightIds)
{
    LONGS_EQUAL(-1,
                LightScheduler_turnOn(-1, Monday, 100 + 2));
    LONGS_EQUAL(
        -1,
        LightScheduler_turnOn(243, Monday, 100 + 3));
    LONGS_EQUAL(-1,
                LightScheduler_turnOn(33, Monday, 100 + 4));
}


TEST_GROUP(lightscheduler_randomize_tests)
{
    int (*temp_address)(void);
    void setup()
    {
        LightController_Create();
        LightScheduler_Create();

        UT_PTR_SET(random_minute_get, FakeRandom_getminute);
    }

    void teardown()
    {
        random_minute_get = temp_address;
    }
};
TEST(lightscheduler_randomize_tests,
     check_simulated_randomness)
{
    LightScheduler_turnOn(3, Monday, 1200);
    FakeRandom_minute_setAndIncrement(-10, 5);
    LightScheduler_randomize(3, Monday, 1200);
    set_time(Monday, 1200 - 10);
    LightScheduler_wakeup();
    check_lights(3, LIGHT_ON);
}
