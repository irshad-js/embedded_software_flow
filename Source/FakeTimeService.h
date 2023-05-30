#ifndef FAKE_TIMESERVICE_H
#define FAKE_TIMESERVICE_H

#include "TimeService.h"

enum
{
    TIME_UNKOWN = -1
};

void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(int day);
int FakeTimeService_GetMinute(void);
int FakeTimeService_GetDay(void);
AlarmCallback FakeTimeService_GetCallback(void);
void FakeTimeService_OneMinuteIsComplete(void);

#endif