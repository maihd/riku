// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <functional>
#include <riku/func.h>

#include <riku/list.h>
#include <riku/array.h>
#include <riku/hash_table.h>
#include <riku/dictionary.h>
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


using FuncList       = List<Func<void(const char*)>>;
using FuncArray      = Array<Func<void(const char*)>>;
using FuncTable      = HashTable<Func<void(const char*)>>;
using FuncDictionary = Dictionary<int, Func<void(const char*)>>;

TEST_CASE("Testing Func<...>", "[Func<>]")
{
    Func<void(const char*)> print  = simple_print;
    Func<void(const char*)> print1 = simple_print;
    Func<void(const char*)> print2 = [](const char* s) { console::log(s); };
    Func<void(const char*)> print3 = make_func(new Printer(), &Printer::print);

    REQUIRE(print);
    REQUIRE(print1);
    REQUIRE(print2);
    REQUIRE(print3);
    REQUIRE(print  == print1);
    REQUIRE(print1 != print2);
    REQUIRE(print2 != print3);
    REQUIRE(print  != nullptr);
    REQUIRE(print1 != nullptr);
    REQUIRE(print2 != nullptr);
    REQUIRE(print3 != nullptr);

    print("Hello world");
    print2("Hello world 2");
    print3("Hello world 3");

    FuncList func_list;
    func_list.push(print);
    func_list.push(print2);
    func_list.push(print3);
    func_list[0]("FuncList: Hello world");
    func_list[1]("FuncList: Hello world 2");
    func_list[2]("FuncList: Hello world 3");

#if 0 && DONOT_USE_THIS_IF_NOT_IT_WILL_CRASH
    //FuncArray func_array;
    //init<decltype(print)>(&table::get_or_add(func_table, 1), print);
    //init<decltype(print)>(&table::get_or_add(func_table, 2), print2);
    //init<decltype(print)>(&table::get_or_add(func_table, 3), print3);

    FuncTable func_table;
    INIT(&func_table.get_or_new(1)) Func<void(const char*)>(print);
    INIT(&func_table.get_or_new(2)) Func<void(const char*)>(print2);
    INIT(&func_table.get_or_new(3)) Func<void(const char*)>(print3);

    func_table.get(1)("FuncTable: Hello world");
    func_table.get(2)("FuncTable: Hello world 2");
    func_table.get(3)("FuncTable: Hello world 3");
#endif

    FuncDictionary func_dict;
    func_dict[1] = print;
    func_dict[2] = print2;
    func_dict[3] = print3;
    func_dict[1]("FuncDictionary: Hello world");
    func_dict[2]("FuncDictionary: Hello world 2");
    func_dict[3]("FuncDictionary: Hello world 3");
}