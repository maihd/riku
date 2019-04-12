// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include <setjmp.h>

#undef setjmp
#undef longjmp

namespace sys
{
    // Long jump saved-point
    using JumpPoint = jmp_buf;

    // Set saved-point to long jump
#if PLATFORM_WINDOWS
    constexpr auto setjmp = ::_setjmp;
#else
    using ::setjmp;
#endif

    // Long jump to the last saved-point
    using ::longjmp;

    // Allocate a memory block from system RAM, with given alignment
    RIKU_API void* alloc(int size, int align);

    // Re-allocate memory block from system RAM, with given alignment
    RIKU_API void* realloc(void* ptr, int size, int align);

    // De-allocate memory block from system RAM
    RIKU_API void  dealloc(void* ptr);
}