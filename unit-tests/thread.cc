#include "./unit_test.h"
#include <riku/thread.h>

TEST_CASE("Thread testing", "[thread]")
{
    Thread* thread = new Thread();
    thread->start([]() {
        console::log("Thread: hello world!");
    });

    thread->wait();
    delete thread;
}