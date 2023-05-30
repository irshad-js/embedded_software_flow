#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"


extern "C"
{
#include "CppUTestExt/MockSupport_c.h"
#include "Flash.h"
#include "IO_read.h"
#include "IO_write.h"

    void IO_write(uint32_t address, uint16_t data)
    {
        mock_c()
            ->actualCall(__func__)
            ->withIntParameters("addr", address)
            ->withIntParameters("data", data);
    }
    uint16_t IO_read(uint32_t address)
    {
        mock_c()->actualCall(__func__)->withIntParameters(
            "addr",
            address);

        return -1;
    }
}

TEST_GROUP(MockBasedTesting){void setup(){

} void teardown(){mock().checkExpectations();
mock().clear();
}
}
;

TEST(MockBasedTesting, Init)
{
    mock().expectOneCall("IO_read").withIntParameter("addr",
                                                     0x90);
    mock()
        .expectOneCall("IO_write")
        .withIntParameter("addr", 1)
        .withIntParameter("data", 2);
    Flash_write(10, 10);
}