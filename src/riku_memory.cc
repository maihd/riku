// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <riku/core.h>

#include <stdlib.h>
#include <string.h>

// Allocate a memory block, with given alignment
void* Allocator::alloc(int size, int align)
{
    return system_memory::alloc(size, align);
}

// Re-allocate memory block, with given alignment
void* Allocator::realloc(void* ptr, int size, int align)
{
    return system_memory::realloc(ptr, size, align);
}

// De-allocate memory block
void  Allocator::dealloc(void* ptr)
{
    return system_memory::dealloc(ptr);
}

namespace system_memory
{
    // Allocate a memory block, with given alignment
    void* alloc(int size, int align)
    {
        if (size > 0)
        {
            ASSERT(align >= 16 && align <= 256, "Alignment must be between [16, 256]");
            ASSERT((align & (align - 1)) == 0, "Aligment must be a POT number");

            return memory::align(::malloc((usize)size + align), align);
        }
        else
        {
            return NULL;
        }
    }

    // Re-allocate memory block, with given alignment
    void* realloc(void* ptr, int size, int align)
    {
        if (size > 0)
        {
            ASSERT(align >= 16 && align <= 256, "Alignment must be between [16, 256]");
            ASSERT((align & (align - 1)) == 0, "Aligment must be a POT number");

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
        else
        {
            return NULL;
        }
    }

    // De-allocate memory block
    void  dealloc(void* ptr)
    {
        if (ptr)
        {
            void* org_ptr = memory::dealign(ptr);
            ::free(org_ptr);
        }
    }
}

namespace memory
{
    // Default global allocator
    static Allocator s_default_allocator;
    Allocator* allocator = &s_default_allocator;

    void* alloc(int size)
    {
        return memory::alloc(size, 16);
    }

    void dealloc(void* ptr)
    {
        if (allocator)
        {
            return allocator->dealloc(ptr);
        }
        else
        {
            system_memory::dealloc(ptr);
        }
    }

    void* realloc(void* ptr, int size)
    {
        return memory::realloc(ptr, size, 16);
    }

    void* alloc(int size, int align)
    {
        if (allocator)
        {
            return allocator->alloc(size, align);
        }
        else
        {
            return system_memory::alloc(size, align);
        }
    }

    void* realloc(void* ptr, int size, int align)
    {
        if (allocator)
        {
            return allocator->realloc(ptr, size, align);
        }
        else
        {
            system_memory::realloc(ptr, size, align);
        }
    }

    void* init(void* dst, int val, int size)
    {
        if (size > 0)
        {
            return ::memset(dst, val, (usize)size);
        }
        else
        {
            return dst;
        }
    }

    void* copy(void* dst, const void* src, int size)
    {
        if (size > 0 && src)
        {
            return ::memcpy(dst, src, (usize)size);
        }
        else
        {
            return dst;
        }
    }

    void* move(void* dst, const void* src, int size)
    {
        if (size > 0 && src)
        {
            return ::memmove(dst, src, (usize)size);
        }
        else
        {
            return dst;
        }
    }

    int compare(const void* a, const void* b, int size)
    {
        if (size > 0 && a && b)
        {
            return ::memcmp(a, b, (usize)size);
        }
        else
        {
            return 1;
        }
    }
}