#include "./unit_test.h"
#include <riku/fs.h>
#include <memory>

TEST_CASE("Filesystem testing", "[fs]")
{
    console::log("cwd: %s", process::cwd());

#if OS_WINDOWS
    const char* path = "x32/debug/riku.unit_tests.exe";
#else
    const char* path = "x32/debug/riku.unit_tests";
#endif

    if (fs::exists(path))
    {
        Buffer content = fs::read_file(path);
        console::log("filesystem done!");

        std::shared_ptr<int> val;
    }
    else
    {
        console::log("filesystem failed!");
    }
}