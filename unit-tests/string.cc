#include "./unit_test.h"

TEST_CASE("String and friend testing", "[str, String, HeapString]")
{
    str str0 = "hello world";
    String string0 = str0;

    console::log("str0 = \"%s\"\n", str0);
    console::log("string0 = \"%s\"\n", string0.buffer);

    HeapString heap_string0 = "hello world from HeapString";
    string0 = heap_string0;
    console::log("heap_string0 = \"%s\"\n", heap_string0.buffer);
    console::log("string0 = \"%s\"\n", string0.buffer);
}