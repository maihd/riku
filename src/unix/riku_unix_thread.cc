#include <riku/core.h>
#include <riku/thread.h>

#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

#if PLATFORM_OSX
#   include <mach/mach.h>
#   include <mach/task.h>
#   include <mach/semaphore.h>
#   include <TargetConditionals.h>
#endif

Atomic& Atomic::operator=(i64 value)
{
#ifdef __ATOMIC_RELAXED
    __atomic_exchange_n(&this->value, value, __ATOMIC_RELAXED);
#else
    this->value = value;
#endif
    return *this;
}

Atomic& Atomic::operator=(const Atomic& other)
{
#ifdef __ATOMIC_RELAXED
    __atomic_exchange_n(&this->value, other.value, __ATOMIC_RELAXED);
#else
    this->value = other.value;
#endif
    return *this;
}

Atomic& operator++(Atomic& atomic)
{
    return (atomic += 1);
}

Atomic& operator--(Atomic& atomic)
{
    return (atomic -= 1);
}

Atomic operator++(Atomic& atomic, int)
{
    auto result = atomic;
    atomic += 1;
    return result;
}

Atomic operator--(Atomic& atomic, int)
{
    auto result = atomic;
    atomic -= 1;
    return result;
}

Atomic& operator+=(Atomic& atomic, i64 value)
{
#ifdef __ATOMIC_RELAXED
    __atomic_add_fetch(&atomic.value, value, __ATOMIC_RELAXED);
#else
    atomic.value += value;
#endif
    return atomic;
}

Atomic& operator-=(Atomic& atomic, i64 value)
{
#ifdef __ATOMIC_RELAXED
    __atomic_sub_fetch(&atomic.value, value, __ATOMIC_RELAXED);
#else
    atomic.value -= value;
#endif
    return atomic;
}

Atomic& operator^=(Atomic& atomic, i64 value)
{
#ifdef __ATOMIC_RELAXED
    __atomic_xor_fetch(&atomic.value, value, __ATOMIC_RELAXED);
#else
    atomic.value ^= value;
#endif
    return atomic;
}

Atomic& operator|=(Atomic& atomic, i64 value)
{   
#ifdef __ATOMIC_RELAXED
    __atomic_or_fetch(&atomic.value, value, __ATOMIC_RELAXED);
#else
    atomic.value |= value;
#endif
    return atomic;
}

Atomic& operator&=(Atomic& atomic, i64 value)
{
#ifdef __ATOMIC_RELAXED
    __atomic_and_fetch(&atomic.value, value, __ATOMIC_RELAXED);
#else
    atomic.value &= value;
#endif
    return atomic;
}

struct Thread::Context : public RefCount
{
    pthread_t  handle;
    ThreadFunc routine;

    void stop(void)
    {
#if PLATFORM_ANDROID
    pthread_kill((pthread_t)handle, SIGUSR1); // pthread_t
#elif PLATFORM_UNIX
    pthread_cancel((pthread_t)handle); // pthread_t
#endif

        handle = 0;
    }

    void wait(void)
    {
        pthread_join((pthread_t)handle, NULL);
    }
};

static void* Thread_native_routine(void* params)
{
    // Run thread routine
    Thread::Context* context = (Thread::Context*)params;
    if (context)
    {
        context->routine();
    }

    // Clean up thread
    context->stop();

    // End of thread
    return NULL;
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
        pthread_create((pthread_t*)&context->handle, NULL, Thread_native_routine, context);
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
    handle = memory::alloc(sizeof(pthread_mutex_t));
    pthread_mutex_init((pthread_mutex_t*)handle, NULL);
}

Mutex::~Mutex(void)
{
    pthread_mutex_destroy((pthread_mutex_t*)handle);
    memory::dealloc(handle);
}

void Mutex::lock(void)
{
    pthread_mutex_lock((pthread_mutex_t*)handle);
}

bool Mutex::trylock(void)
{
    return pthread_mutex_lock((pthread_mutex_t*)handle) == 0;
}

void Mutex::unlock(void)
{
    pthread_mutex_unlock((pthread_mutex_t*)handle);
}

Condition::Condition(void)
{
    handle = memory::alloc(sizeof(pthread_cond_t));
    pthread_cond_init((pthread_cond_t*)handle, NULL);
}

Condition::~Condition(void)
{
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
}

void Condition::wait(const Mutex& mutex)
{
    if (pthread_cond_wait((pthread_cond_t*)handle, (pthread_mutex_t*)mutex.handle))
    {
        process::abort();
    }
}

bool Condition::wait_timeout(const Mutex& mutex, long nanoseconds)
{
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
     * but has this alternative routine instead.
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
}

void Condition::signal(void)
{
    if (pthread_cond_signal((pthread_cond_t*)handle) != 0)
    {
        process::abort();
    }
}

void Condition::broadcast(void)
{
    if (pthread_cond_broadcast((pthread_cond_t*)handle) != 0)
    {
        process::abort();
    }
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
    handle = new (memory::allocator) SemaphoreContext(count);
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
    ((SemaphoreContext*)handle)->~SemaphoreContext();
    memory::dealloc(handle);
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