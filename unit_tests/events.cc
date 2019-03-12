#include <riku/func.h>
#include <riku/events.h>
#include "./unit_test.h"

static void print_something()
{
    console::log("EventEmitter: Hello world");
}

TEST_CASE("Events module testing", "[events]")
{
    //using FuncType = decltype(print_something)*;
    using FuncType = Func<void()>;
    EventEmitter<int, FuncType> caller;

    int event_name = 1;

    caller.on(event_name, print_something);
    caller.once(event_name, print_something);
    
    REQUIRE(caller.emit(event_name) == 2);
    REQUIRE(caller.emit(event_name) == 1);
}