// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/thread.h>
#include "./unit_test.h"

TEST_CASE("Thread testing", "[thread]")
{
    Thread* thread = CREATE(Thread) Thread();
    thread->start([]() {
        int count = 0;
        while (count--)
        {
            console::log("Thread: hello world!");
            performance::sleep(1000);
        }
    });

    thread->wait();
    DESTROY(thread);
}