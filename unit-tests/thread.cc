// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/thread.h>
#include "./unit_test.h"

TEST_CASE("Thread testing", "[thread]")
{
    Thread* thread = create<Thread>();
    thread->start([]() {
        console::log("Thread: hello world!");
    });

    thread->wait();
    destroy(thread);
}