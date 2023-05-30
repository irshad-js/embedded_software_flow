
#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightControllerSpy.h"
}

TEST_GROUP(LightControllerSpy){
    void setup(){LightController_Create();
}
void teardown()
{
    LightController_Destroy();
}
}
;

TEST(LightControllerSpy, Create)
{
    LONGS_EQUAL(LAST_ID_UNKNOWN,
                LightControllerSpy_GetLastId());

    LONGS_EQUAL(LAST_STATE_UNKNOWN,
                LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberLastIdControlled)
{
    lightcontroller_turnon(3);
    LONGS_EQUAL(3, LightControllerSpy_GetLastId());

    LONGS_EQUAL(LIGHT_ON,
                LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, TestMultipleLights)
{
    lightcontroller_turnon(3);
    lightcontroller_turnon(5);
    LONGS_EQUAL(LIGHT_ON,
                LightControllerSpy_GetLastLightState(3));

    LONGS_EQUAL(LIGHT_ON,
                LightControllerSpy_GetLastLightState(5));

    LONGS_EQUAL(LAST_STATE_UNKNOWN,
                LightControllerSpy_GetLastLightState(22));

    lightcontroller_turnoff(4);
    lightcontroller_turnoff(6);
    LONGS_EQUAL(LIGHT_OFF,
                LightControllerSpy_GetLastLightState(4));

    LONGS_EQUAL(LIGHT_OFF,
                LightControllerSpy_GetLastLightState(6));
}
