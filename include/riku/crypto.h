#pragma once

#include "./core.h"

namespace crypto
{
    struct MD5
    {
        uint state[4];
        uint count[2];
        byte buffer[64];
    };

    // Hashing buffer with MD5 algorithm, and return checksum
    __rikuapi ulong md5(MD5& ctx, const void* buffer, usize length);

    // Compute check sum of buffer with CRC32 algorithm
    __rikuapi ulong crc32(const void* buffer, usize length);

    // Compute hash value of buffer with Murmur algorithm
    __rikuapi ulong murmur(const void* buffer, usize length);
    
    // Compute hash value of buffer with Murmur algorithm
    __rikuapi ulong murmur(const void* buffer, usize length, ulong seed);
}