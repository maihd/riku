// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "../core.h"

#if defined(__ARM_NEON)
#if CPU_ARM && !ARCH_64BIT && !PLATFORM_ANDROID        
#define MATH_ENABLE_NEON 0
#else
#include <arm_neon.h>     
#define MATH_ENABLE_NEON 1
#endif         
#else
#define MATH_ENABLE_NEON 0
#endif