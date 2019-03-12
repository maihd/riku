#pragma once

#include "./core.h"
#include "./func.h"

using ThreadFunc = Func<void(void)>;

struct Thread
{ 
public:
#if PLATFORM_WINDOWS
    void* handle; // HANDLE
#elif PLATFORM_UNIX
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

struct Mutex
{
public:
    void* handle;

public:
    __rikuapi Mutex(void);
    __rikuapi ~Mutex(void);

public:
    __rikuapi void lock(void); 
    __rikuapi void unlock(void);
    __rikuapi bool trylock(void);
};

struct Condition
{
public:
    void* handle;
    
public:
    __rikuapi Condition(void);
    __rikuapi ~Condition(void);

public:
    __rikuapi void wait(const Mutex& mutex);
    __rikuapi bool wait_timeout(const Mutex& mutex, long nanoseconds);

    __rikuapi void signal(void); 
    __rikuapi void broadcast(void);
};

struct Semaphore
{
public:
    void* handle;

public:
    __rikuapi Semaphore(int count = 0);
    __rikuapi ~Semaphore(void);

public:
    __rikuapi void wait(void);
    __rikuapi void post(void);
    __rikuapi bool trywait(void);
};