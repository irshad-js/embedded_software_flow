#ifndef RUNTIME_ERROR_STUB_H
#define RUNTIME_ERROR_STUB_H

#include "runtime_error.h"

void RuntimeErrorStub_Reset(void);
const char *RuntimeErrorStub_GetLastError(void);
int RuntimeErrorStub_GetLastParameter(void);


#endif