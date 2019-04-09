// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/thread.h>
#include "./unit_test.h"

TEST_CASE("Thread testing", "[thread]")
{
    Thread* thread = new (memory::allocator) Thread();
    thread->start([]() {
        Atomic count;
        count.value = 10;
        while (count.value > 0)
        {
            console::log("Thread: hello world!");
            performance::sleep(1000);

            count--;
        }
    });

    thread->wait();
    thread->~Thread();
    memory::dealloc(thread);
}