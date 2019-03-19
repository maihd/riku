#include <riku/string.h>
#include <riku/dictionary.h>

#include "./unit_test.h"

TEST_CASE("Dictionary<> compilation and working testing", "[Dictionary<>]")
{
    Dictionary<int, int> dict;

    dict[0] = 10;
    dict[1] = 10;
    dict[2] = 10;
    dict[3] = 10;
    dict[4] = 10;
    dict[5] = 10;
    dict[6] = 10;
    dict[7] = 10;
    dict[8] = 10;
    dict[9] = 10;

    for (int i = 0; i < 10; i++)
    {
        REQUIRE(dict[i] == 10);
        console::log("dict[%d] = %d", i, dict[i]);
    }
}

TEST_CASE("Dictionary<const char*, ...> testing", "[Dictionary<const char*>]")
{
    Dictionary<const char*, const char*> dict;
    dict["greeting"] = "Hello world!";
    dict["sentence"] = "The quick brown fox jumps over the lazy dog";

    const char* tmp = dict["greeting"];
    REQUIRE(string::equal(dict["greeting"], "Hello world!"));
    REQUIRE(string::equal(dict["sentence"], "The quick brown fox jumps over the lazy dog"));
    
    const char* const * keys   = dict.get_keys();
    const char* const * values = dict.get_values();
    for (int i = 0; i < dict.get_length(); i++)
    {
        console::log("dict[\"%s\"] = \"%s\"", keys[i], values[i]);
    }

    int old_length = dict.get_length();
    REQUIRE(dict.remove("sentence"));
    REQUIRE(dict.get_length() == old_length -1);

    keys   = dict.get_keys();
    values = dict.get_values();
    for (int i = 0; i < dict.get_length(); i++)
    {
        console::log("dict[\"%s\"] = \"%s\"", keys[i], values[i]);
    }
}

TEST_CASE("Dictionary<String, ...> testing", "[Dictionary<string>]")
{
    Dictionary<String, String> dict;
    dict["greeting"] = "Hello world!";
    dict["sentence"] = "The quick brown fox jumps over the lazy dog";

    String& temp = dict["greeting"];
    REQUIRE(dict["greeting"] == "Hello world!");
    REQUIRE(dict["sentence"] == "The quick brown fox jumps over the lazy dog");

    const String* keys   = dict.get_keys();
    const String* values = dict.get_values();
    for (int i = 0; i < dict.get_length(); i++)
    {
        console::log("dict[\"%s\"] = \"%s\"", keys[i].get_characters(), values[i].get_characters());
    }

    int old_length = dict.get_length();
    REQUIRE(dict.remove("sentence"));
    REQUIRE(dict.get_length() == old_length - 1);

    keys   = dict.get_keys();
    values = dict.get_values();
    for (int i = 0; i < dict.get_length(); i++)
    {
        console::log("dict[\"%s\"] = \"%s\"", keys[i].get_characters(), values[i].get_characters());
    }
}