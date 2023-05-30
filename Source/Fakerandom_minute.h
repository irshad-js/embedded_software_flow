#ifndef FAKERANDOM_MINUTE_H
#define FAKERANDOM_MINUTE_H

#include "RandomMinute.h"

void FakeRandom_minute_setAndIncrement(int seed,
                                       int increment);
void FakeRandom_minute_reset(void);
int FakeRandom_getminute(void);

#endif