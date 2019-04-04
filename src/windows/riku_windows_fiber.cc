#include <riku/core.h>
#include <riku/thread.h>

#include <Windows.h>

__threadstatic void* s_thread_fiber;
namespace thread_callbacks
{
    static void WINAPI fiber(void* params)
    {
        Fiber* fiber = (Fiber*)params;
        if (fiber->func)
        {
            fiber->func();
        }

        // Switch back to main thread
        ::SwitchToFiber(s_thread_fiber);
    }
}

// Pause current fiber
void Fiber::switch_back(void)
{
    // Switch back to main thread
    ::SwitchToFiber(s_thread_fiber);
}

bool Fiber::init(const ThreadFunc& func)
{
    if (func)
    {
        if (!s_thread_fiber)
        {
            s_thread_fiber = ::ConvertThreadToFiber(NULL);
        }

        handle = ::CreateFiber(0, thread_callbacks::fiber, this);
        if (handle)
        {
            this->func = func;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void Fiber::release(void)
{
    if (handle)
    {
        ::DeleteFiber(handle);
        handle = NULL;
        func   = nullptr;
    }
}

void Fiber::switch_to(void)
{
    if (handle)
    {
        ::SwitchToFiber(handle);
    }
}