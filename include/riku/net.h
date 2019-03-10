// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

struct Socket
{
public:
    int fd;
};

namespace net
{
    Socket socket();
}