#include <riku/str.h>

#include "./unit-test.h"

TEST_CASE("String and friend testing", "[str, String, HeapString]")
{
    str str0 = "hello world";
    String string0 = str0;

    printf("str0 = \"%s\"\n", str0);
    printf("string0 = \"%s\"\n", string0.buffer);

    HeapString heap_string0 = "hello world from HeapString";
    string0 = heap_string0;
    printf("heap_string0 = \"%s\"\n", heap_string0.buffer);
    printf("string0 = \"%s\"\n", string0.buffer);
}