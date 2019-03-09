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
        : handle(NULL)
        {}

public:
    __rikuapi void start(const ThreadFunc& func);
    __rikuapi void stop(void);
    __rikuapi void wait(void);
};