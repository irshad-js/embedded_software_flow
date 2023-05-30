#include "chapter8_lightscheduler.h"

enum
{
    TurnOn = 1,
    TurnOff = 2
};

typedef struct events
{
    int minute;
    int event;
    int id;
    int day;
} scheduled_event_t;

#define MAX_EVENTS 128

static scheduled_event_t scheduled_event[MAX_EVENTS];

void LightScheduler_Create(void)
{
    for (int temp = 0; temp < MAX_EVENTS; temp++)
    {
        scheduled_event[temp].id = UNUSED;
    }
    TimeService_CreateAlarm(60, LightScheduler_wakeup);
}

void LightScheduler_Destroy(void)
{
    TimeService_DestroyAlarm(60, LightScheduler_wakeup);
}
int LightScheduler_turnOn(int id, int day, int time)
{
    if (!(id >= 0 && id <= 31))
    {
        return -1; // error condition out of bounds id
    }

    for (int temp = 0; temp < MAX_EVENTS; temp++)
    {
        if (scheduled_event[temp].id == UNUSED)
        {
            scheduled_event[temp].id = id;
            scheduled_event[temp].event = TurnOn;
            scheduled_event[temp].minute = time;
            scheduled_event[temp].day = day;
            return 0;
        }
    }
    return -1; // error condition // too many events
}

int LightScheduler_turnOff(int id, int day, int time)
{
    if (!(id >= 0 && id <= 31))
    {
        return -1; // error condition out of bounds id
    }

    for (int temp = 0; temp < MAX_EVENTS; temp++)
    {
        if (scheduled_event[temp].id == UNUSED)
        {
            scheduled_event[temp].id = id;
            scheduled_event[temp].event = TurnOff;
            scheduled_event[temp].minute = time;
            scheduled_event[temp].day = day;
            return 0;
        }
    }
    return -1; // error condition // too many events
}

int LightScheduler_scheduleRemove(int id, int day, int time)
{
    if (!(id >= 0 && id <= 31))
    {
        return -1; // error condition out of bounds id
    }

    for (int temp = 0; temp < MAX_EVENTS; temp++)
    {
        if ((scheduled_event[temp].id == id)
            && (scheduled_event[temp].day == day)
            && (scheduled_event[temp].minute == time))
        {
            scheduled_event[temp].id = -1;
            scheduled_event[temp].event = -1;
            scheduled_event[temp].minute = -1;
            scheduled_event[temp].day = -1;
            return 0;
        }
    }
}
void LightScheduler_wakeup(void)
{
    custom_time_t time;
    TimeService_GetTime(&time);
    int today = time.day;
    for (int temp = 0; temp < MAX_EVENTS; temp++)
    {
        if (scheduled_event[temp].id != UNUSED)
        {
            if (scheduled_event[temp].minute
                != time.minute_of_day)
                return;

            if ((scheduled_event[temp].day != today)
                && (scheduled_event[temp].day != Everyday)
                && !((scheduled_event[temp].day == Weekend)
                     && (today == Saturday
                         || today == Sunday))
                && !(((scheduled_event[temp].day == Weekday)
                      && (today >= Monday
                          && today <= Friday))))
                return;
            if (scheduled_event[temp].event == TurnOn)
            {
                lightcontroller_turnon(
                    scheduled_event[temp].id);
            }
            if (scheduled_event[temp].event == TurnOff)
            {
                lightcontroller_turnoff(
                    scheduled_event[temp].id);
            }
        }
    }
}

int LightScheduler_randomize(int id, int day, int time)
{
    if (!(id >= 0 && id <= 31))
    {
        return -1; // error condition out of bounds id
    }

    for (int temp = 0; temp < MAX_EVENTS; temp++)
    {
        if ((scheduled_event[temp].id == id)
            && (scheduled_event[temp].day == day)
            && (scheduled_event[temp].minute == time))
        {
            int temp_val = random_minute_get();
            scheduled_event[temp].minute += temp_val;
        }
    }
}
