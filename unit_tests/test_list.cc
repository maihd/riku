// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

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

namespace traits
{
    template <>
    bool equals<Object>(const Object& a, const Object& b)
    {
        return true;
    }
}

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

    REQUIRE(objects.unshift(Object()));
    REQUIRE(objects.unshift(Object()));
    REQUIRE(objects.unshift(Object()));
    REQUIRE(objects.unshift(Object()));
    REQUIRE(objects.unshift(Object()));
    REQUIRE(objects.unshift(Object()));
    REQUIRE(objects.unshift(Object()));
    REQUIRE(objects.unshift(Object()));

    REQUIRE(objects.remove(Object()));
    REQUIRE(objects.remove(Object()));
    REQUIRE(objects.remove(Object()));
    REQUIRE(objects.remove(Object()));
    REQUIRE(objects.remove(Object()));
    REQUIRE(objects.remove(Object()));
    REQUIRE(objects.remove(Object()));
    REQUIRE(objects.remove(Object()));

    REQUIRE(objects.erase(0));
    REQUIRE(objects.erase(0));
    REQUIRE(objects.erase(0));
    REQUIRE(objects.erase(0));
    REQUIRE(objects.erase(0));
    REQUIRE(objects.erase(0));
    REQUIRE(objects.erase(0));
    REQUIRE(objects.erase(0));
}