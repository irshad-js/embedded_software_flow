#include "CppUTest/TestHarness.h"

extern "C"
{
#include <memory.h>
#include <stdio.h>
}

TEST_GROUP(sprintf){void setup(){

} void teardown(){

}};

#if 0 // START: RefactoredTests
TEST(sprintf, NoFormatOperations)
{
    expect("hey");
    given(sprintf(output, "hey"));
}

TEST(sprintf, InsertString)
{
    expect("Hello World\n");
    given(sprintf(output, "Hello %s\n", "World"));
}
//END: RefactoredTests

#else // START: Duplication
// START: FormatSpace
TEST(sprintf, NoFormatOperations)
{
    char output[5];
    memset(output, 0xaa, sizeof output);

    LONGS_EQUAL(3, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
    BYTES_EQUAL(0xaa, output[4]);
}
// END: FormatSpace

TEST(sprintf, InsertString)
{
    char output[20];
    memset(output, 0xaa, sizeof output);

    LONGS_EQUAL(12, sprintf(output, "%s\n", "Hello World"));
    STRCMP_EQUAL("Hello World\n", output);
    BYTES_EQUAL(0xaa, output[13]);
}
// END: Duplication
#endif

#if 1 // START: NoFormatOperations1
TEST(sprintf, NoFormatOperations2)
{
    char output[5];
    LONGS_EQUAL(3, sprintf(output, "hey"));
    STRCMP_EQUAL("hey\0", output);
}
// END: NoFormatOperations1
#endif
