#pragma once

#include "./core.h"
#include "./func.h"

using ThreadFunc = Func<void(void)>;

struct Thread
{ 
public:
#if OS_WINDOWS
    void* handle; // HANDLE
#elif OS_UNIX
    void* handle; // pthread_t
#endif

    ThreadFunc func;

public:
    inline Thread(void)
        : handle(null)
        {}

public:
    RIKU_API void start(const ThreadFunc& func);
    RIKU_API void stop(void);
    RIKU_API void wait(void);
};