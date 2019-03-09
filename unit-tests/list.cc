#include <riku/list.h>
#include "./unit_test.h"

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