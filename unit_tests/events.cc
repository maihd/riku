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
    EventEmitter<FuncType> caller;
    caller.on(1, print_something);
    caller.emit(1);
}