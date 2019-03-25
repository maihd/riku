#include <riku/path.h>
#include "./unit_test.h"

TEST_CASE("Path module testing", "[path]")
{
#if PLATFORM_WINDOWS
    REQUIRE(path::is_absolute("//server"));    // true
    REQUIRE(path::is_absolute("\\\\server"));  // true
    REQUIRE(path::is_absolute("C:/foo/.."));   // true
    REQUIRE(path::is_absolute("C:\\foo\\..")); // true
    REQUIRE(!path::is_absolute("bar\\baz"));    // false
    REQUIRE(!path::is_absolute("bar/baz"));     // false
    REQUIRE(!path::is_absolute("."));           // false
#else
    REQUIRE(path::is_absolute("/foo/bar")); // true
    REQUIRE(path::is_absolute("/baz/.."));  // true
    REQUIRE(!path::is_absolute("qux/"));     // false
    REQUIRE(!path::is_absolute("."));        // false
#endif

    const char* abs_path0 = path::absolute(".");
    console::log("Path of current working directory is: %s", abs_path0);

    const char* abs_path1 = path::absolute("..");
    console::log("Parent path of current working directory is: %s", abs_path1);

    const char* rel_a = "a/b/c/d/e/f";
    const char* rel_b = "a/b/c/d/e/f/g/h";
    const char* rel_c = path::relative(rel_a, rel_b);
}