// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/os.h>
#include "./unit_test.h"

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

    console::log("os::version: %s", os::version());
    console::log("os::hostname: %s", os::hostname());

    console::log("os::uptime: %lus", (u64)os::uptime());

    os::CPU cpus[64]; // 64 core chip?
    int cpu_count = os::cpus(cpus, lengthof(cpus));
    console::log("os::cpus count: %d", cpu_count);
    for (int i = 0; i < cpu_count; i++)
    {
        console::log("os::cpus #%d: %s - speed: %d", i + 1, cpus[i].model, cpus[i].speed);
    }
}