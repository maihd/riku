#include <riku/thread.h>

#if OS_WINDOWS
#include <Windows.h>
#elif OS_UNIX
#include <pthread.h>
#endif

#if OS_WINDOWS
static DWORD WINAPI thread_routine(void* params)
#elif OS_UNIX
static void* thread_routine(Thread* thread)
#endif
{
    // Run thread routine
    Thread* thread = (Thread*)params;
    thread->func();

    // Clean up thread
    thread->stop();
    thread->func = null;

    // End of thread
#if OS_WINDOWS
    return 0;
#elif OS_UNIX
    return null;
#endif
}

void Thread::start(const ThreadFunc& func)
{
    this->func = func;
    
#if OS_WINDOWS
    handle = (void*)CreateThread(null, 0, thread_routine, this, 0, null); // HANDLE
#elif OS_UNIX
    pthread_create((pthread_t*)&handle, null, thread_routine, this);
#endif
}

void Thread::stop(void)
{
#if OS_WINDOWS
    CloseHandle((HANDLE)handle);
#elif OS_UNIX
    pthread_cancel((pthread_t)handle); // pthread_t
#endif

    handle = null;
}

void Thread::wait(void)
{
#if OS_WINDOWS
    WaitForSingleObject((HANDLE)handle, INFINITE);
#elif OS_UNIX
    pthread_join((pthread_t)thread, null);
#endif
}