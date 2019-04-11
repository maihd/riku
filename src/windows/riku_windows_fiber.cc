#if defined(_MSC_VER)
#pragma warning(disable: 4458) // Params hide member
#else

#endif

#include <riku/core.h>
#include <riku/thread.h>

#include <Windows.h>

namespace
{
    __threadstatic void* s_thread_fiber;
    static void WINAPI Fiber_native_routine(void* params)
    {
        ASSERT(params, "Internal logic error: params must be null");

        Fiber* fiber = (Fiber*)params;
        if (fiber->routine)
        {
            fiber->routine(fiber);
        }

        // Fiber done
        fiber->handle = NULL;
        fiber->switch_back();
    }
}

// Pause current fiber
void Fiber::switch_back(void)
{
    // Switch back to main thread
    ::SwitchToFiber(s_thread_fiber);
}

bool Fiber::init(const Func<void(Fiber*)>& routine)
{
    if (routine)
    {
        if (!s_thread_fiber)
        {
            s_thread_fiber = ::ConvertThreadToFiber(NULL);
        }

        handle = ::CreateFiber(0, Fiber_native_routine, this);
        if (handle)
        {
            this->routine = routine;
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
        handle  = NULL;
        routine = nullptr;
    }
}

bool Fiber::switch_to(void)
{
    if (handle)
    {
        ::SwitchToFiber(handle);
        return true;
    }
    else
    {
        return false;
    }
}