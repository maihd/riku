#include <functional>
#include <riku/func.h>
#include <riku/hash_table.h>
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

using FuncTable = HashTable<Func<void(const char*)>>;

TEST_CASE("Testing Func<...>", "[Func<>]")
{
    Func<void(const char*)> print  = simple_print;
    Func<void(const char*)> print2 = [](const char* s) { console::log(s); };
    Func<void(const char*)> print3 = make_func(new Printer(), &Printer::print);

    FuncTable func_table;
    init<decltype(print)>(&table::get_ref(func_table, 1), print);
    init<decltype(print)>(&table::get_ref(func_table, 2), print2);
    init<decltype(print)>(&table::get_ref(func_table, 3), print3);

    print ("Hello world"); 
    print2("Hello world 2");
    print3("Hello world 3");

    table::get_ref(func_table, 1)("FuncTable: Hello world");
    table::get_ref(func_table, 2)("FuncTable: Hello world 2");
    table::get_ref(func_table, 3)("FuncTable: Hello world 3");
}