// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./list.h"
#include "./array.h"
#include "./buffer.h"

struct StackAllocator : Allocator 
{
public:
    Buffer buffer;
    int    allocated;
    void*  last_block;

public:
    inline StackAllocator()
        : buffer()
        , allocated(0)
        , last_block(NULL)
    {
    }

public:
    RIKU_API virtual void* alloc(int size, int align) override;
    RIKU_API virtual void* realloc(void* ptr, int size, int align) override;
    RIKU_API virtual void  dealloc(void* ptr) override;
};

struct LinearAllocator : Allocator
{
public:
    Buffer buffer;
    int    allocated;

public:
    inline LinearAllocator()
        : buffer()
        , allocated(0)
    {
    }

public:
    RIKU_API virtual void* alloc(int size, int align) override;
    RIKU_API virtual void* realloc(void* ptr, int size, int align) override;
    RIKU_API virtual void  dealloc(void* ptr) override;
};

struct PoolAllocator
{
public:
    List<Array<byte>>   buffers;
    Array<void*>        free_handles;
    int                 block_size;
    int                 bucket_size;
    Allocator*          allocator;

public:
    inline PoolAllocator(int block_size, int bucket_size, Allocator* allocator = memory::allocator)
        : buffers(allocator)
        , free_handles(allocator)
        , block_size(block_size)
        , allocator(allocator)
    {
        ASSERT(block_size > 0, "Invalid block size");
        ASSERT(bucket_size > 0, "Invalid bucket size");
    }

public:
    RIKU_API virtual void  clear(void);
    RIKU_API virtual void* acquire(int count = 1);
    RIKU_API virtual bool  release(void* ptr);
};

#if 0
struct BuddyAllocator : Allocator
{


public:
    RIKU_API virtual void* alloc(int size, int align) override;
    RIKU_API virtual void* realloc(void* ptr, int size, int align) override;
    RIKU_API virtual void  dealloc(void* ptr) override;
};
#endif