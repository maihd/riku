#include <riku/thread.h>

#if PLATFORM_WINDOWS
#include <Windows.h>
#elif PLATFORM_UNIX
#include <pthread.h>
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

void Thread::start(const ThreadFunc& func)
{
    this->func = func;
    
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