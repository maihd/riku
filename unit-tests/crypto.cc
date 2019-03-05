#include "./unit_test.h"
#include <riku/crypto.h>

#define TEST_MD5(text, x0, x1, x2, x3) do { crypto::MD5 md5; crypto::md5(md5, text, sizeof(text)); REQUIRE(md5.state[0] == x0); REQUIRE(md5.state[1] == x1); REQUIRE(md5.state[2] == x2); REQUIRE(md5.state[3] == x3); } while (0)

TEST_CASE("crypto module testing", "[crypto]")
{
    //TEST_MD5("hello world", 0x5eb63bbb, 0xe01eeed0, 0x93cb22bb, 0x8f5acdc3);
}