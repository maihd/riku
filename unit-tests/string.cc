#include "./unit_test.h"

TEST_CASE("String and friend testing", "[const char*, String, HeapString]")
{
    const char* str0 = "hello world";
    String string0 = str0;

    console::log("str0 = \"%s\"", str0);
    console::log("string0 = \"%s\"", string0.buffer);

    HeapString heap_string0 = "hello world from HeapString";
    string0 = heap_string0;
    console::log("heap_string0 = \"%s\"", heap_string0.buffer);
    console::log("string0 = \"%s\"", string0.buffer);
}