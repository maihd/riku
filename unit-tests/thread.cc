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