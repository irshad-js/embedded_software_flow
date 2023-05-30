#ifndef LIGHTCONTROLLER_SPY_H
#define LIGHTCONTROLLER_SPY_H

#include "LightController.h"

enum
{
    LAST_ID_UNKNOWN = -1,
    LAST_STATE_UNKNOWN = -1,
    LIGHT_ON = 1,
    LIGHT_OFF = 0
};

int LightControllerSpy_GetLastId(void);

int LightControllerSpy_GetLastState(void);

int LightControllerSpy_GetLastLightState(int id);

#endif