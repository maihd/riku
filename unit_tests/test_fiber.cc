#include <riku/core.h>
#include <riku/thread.h>

#include "./unit_test.h"

TEST_CASE("Fiber testing", "[fiber]")
{
#if PLATFORM_WINDOWS
    Fiber fiber;

    fiber.init([](){
        console::log("Hello world from fiber!");

        // Switch back to current thread
        Fiber::switch_back();

        console::log("Fiber is continue without say hello again.");

        // Switch back to current thread
        Fiber::switch_back(); // If not call this, system will auto switch back to current thread when progress end
    });

    fiber.switch_to();
    //fiber.switch_to(); // Should just print only one log message
    fiber.release();
#endif
}