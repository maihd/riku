#include <riku/table.h>
#include "./unit_test.h"

TEST_CASE("Table<> testing", "[table]")
{
    
}

TEST_CASE("Table<const char*, ...> testing", "[Dictionary<const char*>]")
{
    Table<const char*, const char*> table;
    table.set("greeting", "Hello world!");
    table.set("sentence", "The quick brown fox jumps over the lazy dog");

    REQUIRE(string::equal(table.get("greeting"), "Hello world!"));
    REQUIRE(string::equal(table.get("sentence"), "The quick brown fox jumps over the lazy dog"));

    const char* const * keys = table.get_keys();
    const char* const * values = table.get_values();
    for (int i = 0; i < table.get_length(); i++)
    {
        console::log("dict[\"%s\"] = \"%s\"", keys[i], values[i]);
    }

    int old_length = table.get_length();
    REQUIRE(table.remove("sentence"));
    REQUIRE(table.get_length() == old_length - 1);

    keys = table.get_keys();
    values = table.get_values();
    for (int i = 0; i < table.get_length(); i++)
    {
        console::log("dict[\"%s\"] = \"%s\"", keys[i], values[i]);
    }
}