#include "./unit_test.h"
#include <riku/thread.h>

TEST_CASE("Thread testing", "[thread]")
{
    Thread* thread = create<Thread>();
    thread->start([]() {
        console::log("Thread: hello world!");
    });

    thread->wait();
    destroy(thread);
}