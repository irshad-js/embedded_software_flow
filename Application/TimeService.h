#ifndef TIMESERVICE_H
#define TIMESERVICE_H

typedef struct Time
{
    int day;
    int minute_of_day;
} custom_time_t;

void TimeService_GetTime(custom_time_t *);
void TimeService_Create(void);
void TimeService_Destroy(void);

typedef void (*AlarmCallback)(void);

void TimeService_CreateAlarm(int period, AlarmCallback);
void TimeService_DestroyAlarm(int period, AlarmCallback);

#endif