#ifndef CHAPTER8_LIGHTSCHEDULER_H
#define CHAPTER8_LIGHTSCHEDULER_H

#include "LightController.h"
#include "RandomMinute.h"
#include "TimeService.h"
enum
{
    Monday = 0,
    Tuesday = 1,
    Wednesday = 2,
    Thursday = 3,
    Friday = 4,
    Saturday = 5,
    Sunday = 6,
    Everyday = 7,
    Weekday = 8,
    Weekend = 9
};

enum
{
    LightId_unknown = -1,
    LightState_unknown = -1
};

enum
{
    UNUSED = -1
};

int LightScheduler_turnOn(int id, int day, int time);
int LightScheduler_turnOff(int id, int day, int time);
void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_wakeup(void);
int LightScheduler_scheduleRemove(int id,
                                  int day,
                                  int time);

int LightScheduler_randomize(int id, int day, int time);
#endif