#pragma once

#include "./core.h"
#include "./func.h"

using ThreadFunc = Func<void(void)>;

struct Atomic 
{
	volatile i64 value;
};
RIKU_API Atomic& operator++(Atomic& atomic);
RIKU_API Atomic& operator--(Atomic& atomic);
RIKU_API Atomic  operator++(Atomic& atomic, int);
RIKU_API Atomic  operator--(Atomic& atomic, int);
RIKU_API Atomic& operator+=(Atomic& atomic, i64 value);
RIKU_API Atomic& operator-=(Atomic& atomic, i64 value);
RIKU_API Atomic& operator^=(Atomic& atomic, i64 value);
RIKU_API Atomic& operator|=(Atomic& atomic, i64 value);
RIKU_API Atomic& operator&=(Atomic& atomic, i64 value);

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
    RIKU_API void start(const ThreadFunc& func);
    RIKU_API void stop(void);
    RIKU_API void wait(void);
};

struct Mutex
{
public:
    void* handle;

public:
    RIKU_API Mutex(void);
    RIKU_API ~Mutex(void);

public:
    RIKU_API void lock(void); 
    RIKU_API void unlock(void);
    RIKU_API bool trylock(void);
};

struct Condition
{
public:
    void* handle;
    
public:
    RIKU_API Condition(void);
    RIKU_API ~Condition(void);

public:
    RIKU_API void wait(const Mutex& mutex);
    RIKU_API bool wait_timeout(const Mutex& mutex, long nanoseconds);

    RIKU_API void signal(void); 
    RIKU_API void broadcast(void);
};

struct Semaphore
{
public:
    void* handle;

public:
    RIKU_API Semaphore(int count = 0);
    RIKU_API ~Semaphore(void);

public:
    RIKU_API void wait(void);
    RIKU_API void post(void);
    RIKU_API bool trywait(void);
};