#include "LightControllerSpy.h"

static int state;
static int id;
static int light[32];

void lightcontroller_turnon(int temp_light)
{
    id = temp_light;
    state = LIGHT_ON;
    if (id >= 0 && id <= 31)
        light[id] = LIGHT_ON;
}
void lightcontroller_turnoff(int temp_light)
{
    id = temp_light;
    state = LIGHT_OFF;
    if (id >= 0 && id <= 31)
        light[id] = LIGHT_OFF;
}

int LightControllerSpy_GetLastLightState(int id)
{
    if (id >= 0 && id <= 31)
        return light[id];
    else
        return -1;
}
void LightController_Create(void)
{
    state = LAST_STATE_UNKNOWN;
    id = LAST_ID_UNKNOWN;
    for (int temp = 0; temp < 32; temp++)
    {
        light[temp] = LAST_STATE_UNKNOWN;
    }
}
void LightController_Destroy(void)
{
}

int LightControllerSpy_GetLastId(void)
{
    return id;
}

int LightControllerSpy_GetLastState(void)
{
    return state;
}