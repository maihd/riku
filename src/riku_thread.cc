#include <riku/core.h>
#include <riku/thread.h>

#include <errno.h>
#include <stdlib.h>
#include <limits.h>

#if PLATFORM_WINDOWS
#include <Windows.h>
#elif PLATFORM_UNIX
#include <pthread.h>
#endif

#if PLATFORM_OSX
#   include <mach/mach.h>
#   include <mach/task.h>
#   include <mach/semaphore.h>
#   include <TargetConditionals.h>
#endif

#if PLATFORM_WINDOWS
static DWORD WINAPI thread_routine(void* params)
#elif PLATFORM_UNIX
static void* thread_routine(void* params)
#endif
{
    // Run thread routine
    Thread* thread = (Thread*)params;
    thread->func();

    // Clean up thread
    thread->stop();
    thread->func = NullPtr();

    // End of thread
#if PLATFORM_WINDOWS
    return 0;
#elif PLATFORM_UNIX
    return NULL;
#endif
}

void Thread::start(const ThreadFunc& _func)
{
    this->func = _func;
    
#if PLATFORM_WINDOWS
    handle = (void*)CreateThread(NULL, 0, thread_routine, this, 0, NULL); // HANDLE
#elif PLATFORM_UNIX
    pthread_create((pthread_t*)&handle, NULL, thread_routine, this);
#endif
}

void Thread::stop(void)
{
#if PLATFORM_WINDOWS
    CloseHandle((HANDLE)handle);
#elif PLATFORM_ANDROID
    pthread_kill((pthread_t)handle, SIGUSR1); // pthread_t
#elif PLATFORM_UNIX
    pthread_cancel((pthread_t)handle); // pthread_t
#endif

    handle = NULL;
}

void Thread::wait(void)
{
#if PLATFORM_WINDOWS
    WaitForSingleObject((HANDLE)handle, INFINITE);
#elif PLATFORM_UNIX
    pthread_join((pthread_t)handle, NULL);
#endif
}

Mutex::Mutex(void)
{
#if PLATFORM_WINDOWS
    handle = memory::alloc(sizeof(CRITICAL_SECTION));
    InitializeCriticalSection((CRITICAL_SECTION*)handle);
#elif PLATFORM_UNIX
    handle = memory::alloc(sizeof(pthread_mutex_t));
    pthread_mutex_init((pthread_mutex_t*)handle, NULL);
#endif
}

Mutex::~Mutex(void)
{
#if PLATFORM_WINDOWS
    DeleteCriticalSection((CRITICAL_SECTION*)handle);
    memory::dealloc(handle);
#elif PLATFORM_UNIX
    pthread_mutex_destroy((pthread_mutex_t*)handle);
    memory::dealloc(handle);
#endif
}

void Mutex::lock(void)
{
#if PLATFORM_WINDOWS
    EnterCriticalSection((CRITICAL_SECTION*)handle);
#elif PLATFORM_UNIX
    pthread_mutex_lock((pthread_mutex_t*)handle);
#endif
}

bool Mutex::trylock(void)
{
#if PLATFORM_WINDOWS
    return TryEnterCriticalSection((CRITICAL_SECTION*)handle);
#elif PLATFORM_UNIX
    return pthread_mutex_lock((pthread_mutex_t*)handle) == 0;
#endif
}

void Mutex::unlock(void)
{
#if PLATFORM_WINDOWS
    LeaveCriticalSection((CRITICAL_SECTION*)handle);
#elif PLATFORM_UNIX
    pthread_mutex_unlock((pthread_mutex_t*)handle);
#endif
}

Condition::Condition(void)
{
#if PLATFORM_WINDOWS
    handle = memory::alloc(sizeof(CONDITION_VARIABLE));
    InitializeConditionVariable((CONDITION_VARIABLE*)handle);
#elif PLATFORM_UNIX
    handle = memory::alloc(sizeof(pthread_cond_t));
    pthread_cond_init((pthread_cond_t*)handle, NULL);
#endif
}

Condition::~Condition(void)
{
#if PLATFORM_WINDOWS
    memory::dealloc(handle);
#elif PLATFORM_UNIX
#if defined(__APPLE__) && defined(__MACH__)
    /* It has been reported that destroying condition variables that have been
     * signalled but not waited on can sometimes result in application crashes.
     * See https://codereview.chromium.org/1323293005.
     */
    pthread_mutex_t mutex;
    struct timespec ts;
    int err;

    if (pthread_mutex_init(&mutex, NULL))
    {
        process::abort();
    }

    if (pthread_mutex_lock(&mutex))
    {
        process::abort();
    }

    ts.tv_sec = 0;
    ts.tv_nsec = 1;

    err = pthread_cond_timedwait_relative_np((CONDITION_VARIABLE*)handle, &mutex, &ts);
    if (err != 0 && err != ETIMEDOUT)
    {
        process::abort();
    }

    if (pthread_mutex_unlock(&mutex))
    {
        process::abort();
    }

    if (pthread_mutex_destroy(&mutex))
    {
        process::abort();
    }
#endif /* defined(__APPLE__) && defined(__MACH__) */

    if (pthread_cond_destroy((pthread_cond_t*)handle) != 0)
    {
        process::abort();
    }

    memory::dealloc(handle);
#endif
}

void Condition::wait(const Mutex& mutex)
{
#if PLATFORM_WINDOWS
    if (SleepConditionVariableCS((CONDITION_VARIABLE*)handle, (CRITICAL_SECTION*)mutex.handle, INFINITE))
    {
        process::abort();
    }
#elif PLATFORM_UNIX
    if (pthread_cond_wait((pthread_cond_t*)handle, (pthread_mutex_t*)mutex.handle))
    {
        process::abort();
    }
#endif
}

bool Condition::wait_timeout(const Mutex& mutex, long nanoseconds)
{
#if PLATFORM_WINDOWS
    if (SleepConditionVariableCS((CONDITION_VARIABLE*)handle, (CRITICAL_SECTION*)mutex.handle, (DWORD)(nanoseconds * 1e-6)))
    {
        return true;
    }
    else if (GetLastError() != ERROR_TIMEOUT)
    {
        process::abort();
    }
    return true;
#elif PLATFORM_UNIX
    int r;
    struct timespec ts;
#if defined(__MVS__)
    struct timeval tv;
#endif

#if defined(__APPLE__) && defined(__MACH__)
    ts.tv_sec = timeout / NANOSEC;
    ts.tv_nsec = timeout % NANOSEC;
    r = pthread_cond_timedwait_relative_np((pthread_cond_t*)handle, mutex, &ts);
#else
#if defined(__MVS__)
    if (gettimeofday(&tv, NULL))
    {
        process::abort();
    }
    timeout += tv.tv_sec * NANOSEC + tv.tv_usec * 1e3;
#else
    //timeout += uv__hrtime(UV_CLOCK_PRECISE);
#endif
    ts.tv_sec  = nanoseconds / 1000000000;
    ts.tv_nsec = nanoseconds % 1000000000;
#if defined(__ANDROID_API__) && __ANDROID_API__ < 21

    /*
     * The bionic pthread implementation doesn't support CLOCK_MONOTONIC,
     * but has this alternative function instead.
     */
    r = pthread_cond_timedwait_monotonic_np((pthread_cond_t*)handle, (pthread_mutex_t*)mutex.handle, &ts);
#else
    r = pthread_cond_timedwait((pthread_cond_t*)handle, (pthread_mutex_t*)mutex.handle, &ts);
#endif /* __ANDROID_API__ */
#endif


    if (r == 0)
    {
        return true;
    }

    if (r == ETIMEDOUT)
    {
        return false;
    }

    process::abort();
    return false; /* Satisfy the compiler. */
#endif
}

void Condition::signal(void)
{
#if PLATFORM_WINDOWS
    WakeConditionVariable((CONDITION_VARIABLE*)handle);
#elif PLATFORM_UNIX
    if (pthread_cond_signal((pthread_cond_t*)handle) != 0)
    {
        process::abort();
    }
#endif
}

void Condition::broadcast(void)
{
#if PLATFORM_WINDOWS
    WakeAllConditionVariable((CONDITION_VARIABLE*)handle);
#elif PLATFORM_UNIX
    if (pthread_cond_broadcast((pthread_cond_t*)handle) != 0)
    {
        process::abort();
    }
#endif
}

#if PLATFORM_UNIX
#define USE_CUSTOM_SEMAPHORE 1
#else
#define USE_CUSTOM_SEMAPHORE 0
#endif

#if USE_CUSTOM_SEMAPHORE
struct SemaphoreContext
{
    int       count;
    Mutex     mutex;
    Condition condition;

    SemaphoreContext(int count)
        : count(count)
        {}
};
#endif

Semaphore::Semaphore(int count)
{
#if USE_CUSTOM_SEMAPHORE
    handle = CREATE(SemaphoreContext) SemaphoreContext(count);
#elif PLATFORM_WINDOWS
    handle = CreateSemaphoreA(NULL, count, INT_MAX, NULL);
#elif PLATFORM_OSX
    kern_return_t err = semaphore_create(mach_task_self(), (semaphore_t*)&handle, SYNC_POLICY_FIFO, count);
    if (err != KERN_SUCCESS)
    {
        process::abort();
    }
#endif
}

Semaphore::~Semaphore(void)
{
#if USE_CUSTOM_SEMAPHORE
    DESTROY((SemaphoreContext*)handle);
#elif PLATFORM_WINDOWS
    CloseHandle((HANDLE)handle);
#elif PLATFORM_OSX
    if (semaphore_destroy(mach_task_self(), (semaphore_t)handle))
    {
        process::abort();
    }
#endif
}

void Semaphore::wait(void)
{
#if USE_CUSTOM_SEMAPHORE
    SemaphoreContext* ctx = (SemaphoreContext*)handle;

    ctx->mutex.lock();
    while (ctx->count <= 0)
    {
        ctx->condition.wait(ctx->mutex);
    }
    ctx->count--;
    ctx->mutex.unlock();
#elif PLATFORM_WINDOWS
    if (WaitForSingleObject((HANDLE)handle, INFINITE) != WAIT_OBJECT_0)
    {
        process::abort();
    }
#elif PLATFORM_OSX
    int r;
    do
        r = semaphore_wait((semaphore_t)handle);
    while (r == KERN_ABORTED);

    if (r != KERN_SUCCESS)
    {
        process::abort();
    }
#endif
}

void Semaphore::post(void)
{
#if USE_CUSTOM_SEMAPHORE
    SemaphoreContext* ctx = (SemaphoreContext*)handle;

    ctx->mutex.lock();
    ctx->count++;
    if (ctx->count == 1)
    {
        ctx->condition.signal();
    }
    ctx->mutex.unlock();
#elif PLATFORM_WINDOWS
    if (!ReleaseSemaphore((HANDLE)handle, 1, NULL))
    {
        process::abort();
    }
#elif PLATFORM_OSX
    if (semaphore_signal((semaphore_t)handle))
    {
        process::abort();
    }
#endif
}

bool Semaphore::trywait(void)
{
#if USE_CUSTOM_SEMAPHORE
    SemaphoreContext* ctx = (SemaphoreContext*)handle;

    if (!ctx->mutex.trylock())
    {
        return false;
    }

    if (ctx->count <= 0)
    {
        ctx->mutex.unlock();
        return false;
    }

    ctx->count--;
    ctx->mutex.unlock();

    return 0;
#elif PLATFORM_WINDOWS
    DWORD r = WaitForSingleObject((HANDLE)handle, 0);

    if (r == WAIT_OBJECT_0)
    {
        return true;
    }

    if (r == WAIT_TIMEOUT)
    {
        return false;
    }

    abort();
    return false; /* Satisfy the compiler. */
#elif PLATFORM_OSX
    mach_timespec_t interval;
    kern_return_t err;

    interval.tv_sec = 0;
    interval.tv_nsec = 0;

    err = semaphore_timedwait((semaphore_t)handle, interval);
    if (err == KERN_SUCCESS)
        return true;
    if (err == KERN_OPERATION_TIMED_OUT)
        return false;

    process::abort();
    return false; /* Satisfy the compiler. */
#endif
}