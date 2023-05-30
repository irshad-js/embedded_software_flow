#include "Fakerandom_minute.h"

static int seed;
static int increment;

void FakeRandom_minute_reset(void)
{
    seed = -1;
    increment = -1;
}
int FakeRandom_getminute(void)
{
    int result = seed;
    seed += increment;
    return result;
}

void FakeRandom_minute_setAndIncrement(int temp_seed,
                                       int temp_increment)
{
    seed = temp_seed;
    increment = temp_increment;
}