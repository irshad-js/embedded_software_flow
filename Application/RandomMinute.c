#include "RandomMinute.h"
#include <stdlib.h>

static int seed;
static int increment;
enum
{
    bound = 30
};

void random_minute_create(void)
{
    srand(10);
}
int random_minute_get_implementation(void)
{
    return bound - rand() % (bound * 2 + 1);
    // thus we get values in range -30 to +30
}

int (*random_minute_get)(void)
    = random_minute_get_implementation;