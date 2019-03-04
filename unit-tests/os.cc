#include "./unit_test.h"
#include <riku/os.h>

TEST_CASE("OS module testing", "[os]")
{
    const char* temp = os::tmpdir();
    const char* home = os::homedir();

    console::log("temp: %s", temp);
    console::log("home: %s", home);

    usize fmem = os::freemem();
    usize tmem = os::totalmem();
    console::log("fmem: %u", fmem);
    console::log("tmem: %u", tmem);
}