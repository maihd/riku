// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include "./unit_test.h"
#include <riku/crypto.h>

#define TEST_MD5(text, x0, x1, x2, x3) do { crypto::MD5 md5; crypto::md5(md5, text, sizeof(text)); REQUIRE(md5.state[0] == x0); REQUIRE(md5.state[1] == x1); REQUIRE(md5.state[2] == x2); REQUIRE(md5.state[3] == x3); } while (0)
#define TEST_MURMUR(text, value) REQUIRE(crypto::murmur(text, sizeof(text) - 1) == value)//console::log("crypto::murmur(\"" text "\") = 0x%lx", crypto::murmur(text, sizeof(text)))
#define TEST_CRC32(text, value) REQUIRE(crypto::crc32(text, sizeof(text) - 1) == value)//console::log("crypto::murmur(\"" text "\") = 0x%lx", crypto::murmur(text, sizeof(text)))

TEST_CASE("crypto module testing", "[crypto]")
{
    //TEST_MD5("hello world", 0x5eb63bbb, 0xe01eeed0, 0x93cb22bb, 0x8f5acdc3);

    TEST_MURMUR("hello world", 1586663183);
    TEST_MURMUR("Hello World", 427197390);
   
    TEST_CRC32("hello world", 0x0D4A1185);
    TEST_CRC32("Hello World", 0x4A17B156);
}