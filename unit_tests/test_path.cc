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
}