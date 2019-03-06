#include "./unit_test.h"
#include <riku/list.h>

struct Object
{
    int value;

    constexpr Object(void)
        : value(0)
    {
    }  

    inline ~Object(void)
    {
    }
};

TEST_CASE("List<> testing", "[list]")
{
    List<Object> objects; 

    REQUIRE(objects.push(Object()));
    REQUIRE(objects.push(Object()));
    REQUIRE(objects.push(Object()));
    REQUIRE(objects.push(Object()));
    REQUIRE(objects.push(Object()));
    REQUIRE(objects.push(Object()));
    REQUIRE(objects.push(Object()));
    REQUIRE(objects.push(Object()));
}