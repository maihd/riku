// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace crypto
{
    struct MD5
    {
        u32  state[4];
        u32  count[2];
        byte buffer[64];
    };

    // Hashing buffer with MD5 algorithm, and return checksum
    RIKU_API u32 md5(MD5& ctx, const void* buffer, int length);

    // Compute check sum of buffer with CRC32 algorithm
    RIKU_API u32 crc32(const void* buffer, int length);

    // Compute check sum of buffer with CRC32 algorithm
    RIKU_API u32 crc32(const void* buffer, int length, u32 seed);

    // Compute check sum of buffer with CRC64 algorithm
    RIKU_API u64 crc64(const void* buffer, int length);

    // Compute check sum of buffer with CRC64 algorithm
    RIKU_API u64 crc64(const void* buffer, int length, u64 seed);

    // Compute hash value of buffer with Murmur32 algorithm
    RIKU_API u32 murmur32(const void* buffer, int length);
    
    // Compute hash value of buffer with Murmur32 algorithm
    RIKU_API u32 murmur32(const void* buffer, int length, u32 seed);

    // Compute hash value of buffer with Murmur64 algorithm
    RIKU_API u64 murmur64(const void* buffer, int length);

    // Compute hash value of buffer with Murmur64 algorithm
    RIKU_API u64 murmur64(const void* buffer, int length, u64 seed);
}