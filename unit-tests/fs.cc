#include "./unit_test.h"
#include <riku/fs.h>

TEST_CASE("Filesystem testing", "[fs]")
{
#if OS_WINDOWS
    if (fs::exists("riku.unit-tests.exe"))
#else
    if (fs::exists("riku.unit-tests"))
#endif
    {
        console::log("filesystem done!");
    }
    else
    {
        console::log("filesystem failed!");
    }
}