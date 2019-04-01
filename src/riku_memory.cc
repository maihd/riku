// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/core.h>

#include <stdlib.h>
#include <string.h>

namespace memory
{
    void* alloc(int size)
    {
        return memory::alloc(size, 16);
    }

    void dealloc(void* ptr)
    {
        if (ptr)
        {
            void* org_ptr = memory::dealign(ptr);
            ::free(org_ptr);
        }
    }

    void* realloc(void* ptr, int size)
    {
        return memory::realloc(ptr, size, 16);
    }

    void* alloc(int size, int align)
    {
        return memory::align(::malloc((usize)size + align), align);
    }

    void* realloc(void* ptr, int size, int align)
    {
        if (ptr)
        {
            void* org_ptr = memory::dealign(ptr);
            return memory::align(::realloc(org_ptr, (usize)(size + align)), align);
        }
        else
        {
            return memory::alloc(size, align);
        }
    }

    void* init(void* dst, int val, int size)
    {
        return ::memset(dst, val, (usize)size);
    }

    void* copy(void* dst, const void* src, int size)
    {
        return ::memcpy(dst, src, (usize)size);
    }

    void* move(void* dst, const void* src, int size)
    {
        return ::memmove(dst, src, (usize)size);
    }

    int compare(const void* a, const void* b, int size)
    {
        return ::memcmp(a, b, (usize)size);
    }
}