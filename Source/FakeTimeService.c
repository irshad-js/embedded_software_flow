#include "FakeTimeService.h"

static custom_time_t time;
static AlarmCallback callback;
static int period;

void TimeService_Create(void)
{
    time.day = -1;
    time.minute_of_day = -1;
    callback = NULL;
    period = -1;
}
void TimeService_Destroy(void)
{
}

void TimeService_CreateAlarm(int temp_period,
                             AlarmCallback functionptr)
{
    period = temp_period;
    callback = functionptr;
}

void TimeService_DestroyAlarm(int temp_period,
                              AlarmCallback functionptr)
{
    if (period == temp_period && functionptr == callback)
    {
        period = -1;
        callback = NULL;
    }
}
void TimeService_GetTime(custom_time_t *tempdata)
{
    tempdata->day = time.day;
    tempdata->minute_of_day = time.minute_of_day;
}

void FakeTimeService_SetMinute(int minute)
{
    time.minute_of_day = minute;
}
void FakeTimeService_SetDay(int day)
{
    time.day = day;
}

int FakeTimeService_GetMinute(void)
{
    return time.minute_of_day;
}

int FakeTimeService_GetDay(void)
{
    return time.day;
}

AlarmCallback FakeTimeService_GetCallback(void)
{
    return callback;
}

void FakeTimeService_OneMinuteIsComplete(void)
{
    if (callback != NULL)
        callback();
}