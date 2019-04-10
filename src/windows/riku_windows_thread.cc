#if defined(_MSC_VER)
#   pragma warning(disable: 4458) // Params hide member
#endif

#include <riku/core.h>
#include <riku/thread.h>

#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <Windows.h>

Atomic& operator++(Atomic& atomic)
{
#if ARCH_64BIT
	_InterlockedIncrement64(&atomic.value);
#else
    _InterlockedIncrement((volatile u32*)&atomic.value);
#endif

    return atomic;
}

Atomic& operator--(Atomic& atomic)
{
#if ARCH_64BIT
	_InterlockedDecrement64(&atomic.value);
#else
    _InterlockedDecrement((volatile u32*)&atomic.value);
#endif

    return atomic;
}

Atomic operator++(Atomic& atomic, int)
{
    auto result = atomic;

#if ARCH_64BIT
	_InterlockedIncrement64(&atomic.value);
#else
    _InterlockedIncrement((volatile u32*)&atomic.value);
#endif

    return result;
}

Atomic operator--(Atomic& atomic, int)
{
    auto result = atomic;
    
#if ARCH_64BIT
	_InterlockedDecrement64(&atomic.value);
#else
    _InterlockedDecrement((volatile u32*)&atomic.value);
#endif

    return result;
}

Atomic& operator+=(Atomic& atomic, i64 value)
{
#if ARCH_64BIT
	_InterlockedAdd64(&atomic.value, value);
#else
    _InterlockedAdd((volatile LONG*)&atomic.value, (LONG)value);
#endif

    return atomic;
}

Atomic& operator-=(Atomic& atomic, i64 value)
{
#if ARCH_64BIT
	_InterlockedAdd64(&atomic.value, -value);
#else
    _InterlockedAdd((volatile LONG*)&atomic.value, (LONG)-value);
#endif

    return atomic;
}

Atomic& operator^=(Atomic& atomic, i64 value)
{
#if ARCH_64BIT
	_InterlockedXor64(&atomic.value, value);
#else
    _InterlockedXor((volatile LONG*)&atomic.value, (LONG)value);
#endif

    return atomic;
}

Atomic& operator|=(Atomic& atomic, i64 value)
{
#if ARCH_64BIT
	_InterlockedOr64(&atomic.value, value);
#else
    _InterlockedOr((volatile LONG*)&atomic.value, (LONG)value);
#endif

    return atomic;
}

Atomic& operator&=(Atomic& atomic, i64 value)
{
    
#if ARCH_64BIT
	_InterlockedAnd64(&atomic.value, value);
#else
    _InterlockedAnd((volatile LONG*)&atomic.value, (LONG)value);
#endif

    return atomic;
}

struct Thread::Context : public RefCount
{
    HANDLE     handle;
    ThreadFunc routine;

    void stop(void)
    {
        CloseHandle((HANDLE)handle);

        handle = NULL;
    }

    void wait(void)
    {
        WaitForSingleObject(handle, INFINITE);
    }
};

static DWORD WINAPI Thread_native_routine(void* params)
{
    // Run thread routine
    Thread::Context* context = (Thread::Context*)params;
    if (context->routine)
    {
        context->routine();
    }

    // Clean up thread
    context->stop();

    // End of thread
    return 0;
}

void Thread::start(const ThreadFunc& routine)
{
    if (routine)
    {
        if (!context)
        {
            context = new (memory::allocator) Context();
        }

        context->_incref();
        context->routine = routine;
        context->handle  = CreateThread(NULL, 0, Thread_native_routine, context, 0, NULL); // HANDLE
    }
}

void Thread::stop(void)
{
    if (context)
    {
        context->stop();
        this->~Thread();
    }
}

void Thread::wait(void)
{
    if (context)
    {
        context->wait();
    }
}

Thread::~Thread(void)
{
    if (context && context->_decref() <= 0)
    {
        context->~Context();
        memory::dealloc(context);
    }
}

Thread::Thread(const Thread& other)
    : context(other.context)
{
    if (context)
    {
        context->_incref();
    }
}

Thread& Thread::operator=(const Thread& other)
{
    context = other.context;
    if (context)
    {
        context->_incref();
    }

    return *this;
}

Mutex::Mutex(void)
{
    handle = memory::alloc(sizeof(CRITICAL_SECTION));
    InitializeCriticalSection((CRITICAL_SECTION*)handle);
}

Mutex::~Mutex(void)
{
    DeleteCriticalSection((CRITICAL_SECTION*)handle);
    memory::dealloc(handle);
}

void Mutex::lock(void)
{
    EnterCriticalSection((CRITICAL_SECTION*)handle);
}

bool Mutex::trylock(void)
{
    return TryEnterCriticalSection((CRITICAL_SECTION*)handle);
}

void Mutex::unlock(void)
{
    LeaveCriticalSection((CRITICAL_SECTION*)handle);
}

Condition::Condition(void)
{
    handle = memory::alloc(sizeof(CONDITION_VARIABLE));
    InitializeConditionVariable((CONDITION_VARIABLE*)handle);
}

Condition::~Condition(void)
{
    memory::dealloc(handle);
}

void Condition::wait(const Mutex& mutex)
{
    if (SleepConditionVariableCS((CONDITION_VARIABLE*)handle, (CRITICAL_SECTION*)mutex.handle, INFINITE))
    {
        process::abort();
    }
}

bool Condition::wait_timeout(const Mutex& mutex, long nanoseconds)
{
    if (SleepConditionVariableCS((CONDITION_VARIABLE*)handle, (CRITICAL_SECTION*)mutex.handle, (DWORD)(nanoseconds * 1e-6)))
    {
        return true;
    }
    else if (GetLastError() != ERROR_TIMEOUT)
    {
        process::abort();
    }
    return true;
}

void Condition::signal(void)
{
    WakeConditionVariable((CONDITION_VARIABLE*)handle);
}

void Condition::broadcast(void)
{
    WakeAllConditionVariable((CONDITION_VARIABLE*)handle);
}

Semaphore::Semaphore(int count)
{
    handle = CreateSemaphoreA(NULL, count, INT_MAX, NULL);
}

Semaphore::~Semaphore(void)
{
    CloseHandle((HANDLE)handle);
}

void Semaphore::wait(void)
{
    if (WaitForSingleObject((HANDLE)handle, INFINITE) != WAIT_OBJECT_0)
    {
        process::abort();
    }
}

void Semaphore::post(void)
{
    if (!ReleaseSemaphore((HANDLE)handle, 1, NULL))
    {
        process::abort();
    }
}

bool Semaphore::trywait(void)
{
    DWORD r = WaitForSingleObject((HANDLE)handle, 0);

    if (r == WAIT_OBJECT_0)
    {
        return true;
    }

    if (r == WAIT_TIMEOUT)
    {
        return false;
    }

    process::abort();
    return false; /* Satisfy the compiler. */
}