#include <riku/sys.h>
#include <riku/array.h>
#include <riku/thread.h>

#include <ucontext.h>

struct FiberContext
{
    ucontext_t caller;
    ucontext_t callee;  
};

namespace
{
    constexpr int STACK_SIZE = 2097152 + 16384;
}

void Fiber_native_routine(Fiber* fiber)
{
    if (fiber->routine)
    {
        fiber->routine(fiber);
    }

    // Switch back to thread
    fiber->switch_back();
}

void Fiber::switch_back(void)
{
    FiberContext* context = (FiberContext*)handle;
    if (context)
    {
        swapcontext(&context->callee, &context->caller);
    }
}

bool Fiber::init(const Func<void(Fiber*)>& routine)
{
    if (routine)
    {
        FiberContext* context = (FiberContext*)memory::alloc(sizeof(FiberContext));
        if (context)
        {
            getcontext(&context->callee);
            if (!(context->callee.uc_stack.ss_sp = memory::alloc(STACK_SIZE)))
            {
                memory::dealloc(context);
                context = NULL;
                return false;
            }

            context->callee.uc_link = &context->caller;
            context->callee.uc_stack.ss_size = STACK_SIZE - sizeof(long);
            context->callee.uc_stack.ss_flags = 0;
            makecontext(&context->callee, (void(*)())Fiber_native_routine, 1, this);

            this->handle  = context;
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
        memory::dealloc(handle);

        handle  = NULL;
        routine = nullptr;
    }
}


bool Fiber::switch_to(void)
{
    FiberContext* context = (FiberContext*)handle;
    if (context)
    {
        swapcontext(&context->caller, &context->callee);

        return true;
    }
    else
    {
        return false;
    }
}