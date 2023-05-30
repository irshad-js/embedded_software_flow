#include "Flash.h"
#include "IO_read.h"
#include "IO_write.h"

int Flash_write(uint32_t address, uint16_t data)
{
    IO_read(0x90);
    IO_write(0x1, 02);
    return -1;
}