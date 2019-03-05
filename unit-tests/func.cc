#include <functional>
#include <riku/func.h>
#include "./unit_test.h"

void simple_print(const char* s)
{
    console::log("%s", s);
}

struct Printer
{
    void print(const char* s)
    {
        console::log(s);
    }
};

TEST_CASE("Testing Func<...>", "[Func<>]")
{
    Func<void(const char*)> print  = simple_print;
    Func<void(const char*)> print2 = [](const char* s) { console::log(s); };
    Func<void(const char*)> print3 = make_func(new Printer(), &Printer::print);

    print("Hello world"); 
    print2("Hello world 2");
    print3("Hello world 3");
}