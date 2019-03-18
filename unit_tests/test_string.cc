// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/string.h>
#include "./unit_test.h"

TEST_CASE("String and friend testing", "[const char*, String, HeapString]")
{
    const char* str0 = "hello world";
    String string0 = str0;
    String string1 = "the quick brown fox jumps over the lazy dog";
    console::log("string1 = \"%s\"", string1.get_characters());

    REQUIRE(string0 == str0);

    console::log("str0 = \"%s\"", str0);
    console::log("string0 = \"%s\"", (const char*)string0);

    string1 = string0;
    REQUIRE(string1 == string0);
    REQUIRE(string1.buffer != string0.buffer);

    string1 = "Hello world from the difference world!";
    REQUIRE(string0 != string1);
    REQUIRE(string0 >= string1);
    REQUIRE(string1 <= string0);

    String heap_string0 = "hello world from HeapString";
    string0 = heap_string0;
    console::log("heap_string0 = \"%s\"", (const char*)heap_string0);
    console::log("string0 = \"%s\"", (const char*)string0);

    REQUIRE(string::compare(string::format("Hello world %d", 0), "Hello world 0") == 0);

    char buffer[2048];
    REQUIRE(string::compare(string::format(buffer, sizeof(buffer), "Hello world %d", 0), "Hello world 0") == 0);

    const char* tmp = "hello world";
    u32 tmp_hash1 = calc_hash32("hello world");
    u32 tmp_hash0 = calc_hash32(tmp);
    switch (tmp_hash0)
    {
    case calc_hash32("hello world"):
        REQUIRE(true);
        break;

    default:
        REQUIRE(false);
        break;
    }
}