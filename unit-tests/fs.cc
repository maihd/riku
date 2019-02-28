#include "./unit_test.h"
#include <riku/fs.h>

TEST_CASE("Filesystem testing", "[fs]")
{
    console::log("cwd: %s", process::cwd().buffer);

#if OS_WINDOWS
    str path = "x32/debug/riku.unit_tests.exe";
#else
    str path = "x32/debug/riku.unit_tests";
#endif

    if (fs::exists(path))
    {
        Buffer content = fs::read_file(path);
        console::log("filesystem done!");
    }
    else
    {
        console::log("filesystem failed!");
    }
}