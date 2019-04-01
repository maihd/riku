// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace net
{
    struct Socket
    {
    public:
        int  handle;
        bool is_server;

    public:
        RIKU_API Socket(void);
        RIKU_API ~Socket(void);

    public: 
        RIKU_API void   close(void);
        RIKU_API Socket accept(void);
        RIKU_API int    recv(void* buffer, int length);
        RIKU_API int    send(const void* buffer, int length);
    };

    RIKU_API bool is_ip(const char* input);
    RIKU_API bool is_ipv4(const char* input);
    RIKU_API bool is_ipv6(const char* input);

    RIKU_API Socket connect(const char* host, int port);
    RIKU_API Socket create_server(const char* host, int port);
}