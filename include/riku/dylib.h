// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace dylib
{
    __rikuapi void* open(const char* path);
    __rikuapi bool  close(void* handle);
    __rikuapi void* symbol(void* handle, const char* name);
}