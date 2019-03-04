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