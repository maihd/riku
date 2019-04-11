#include <riku/core.h>
#include <riku/thread.h>

int main(void)
{
    Fiber fiber;
    Fiber fiber1;

    fiber.init([](Fiber* fiber){
        console::log("Hello world from fiber!");

        // Switch back to current thread
        fiber->switch_back();

        console::log("Fiber is continue without say hello again.");

        // Switch back to current thread
        fiber->switch_back(); // If not call this, system will auto switch back to current thread when progress end
    });

    fiber1.init([](Fiber* fiber){
       console::log("Hello world from other fiber!");
    });

    fiber.switch_to();
    fiber1.switch_to();

    console::log("Restart fiber");
    fiber.switch_to(); // When no have this line: should just print only one log message

    console::log("Release all fibers");
    fiber.release(); // no need to call release when fiber done
    fiber1.release(); // no need to call release when fiber done

    return 0;
}