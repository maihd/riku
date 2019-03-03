#pragma once

#include "./core.h"
#include <malloc.h>

template <typename T>
struct Func;

template <typename R, typename ...Args>
struct Func<R(Args...)>
{
public:
    struct Stub;

    using FuncType = R(*)(Args...);
    using StubFunc = R(*)(Stub* stub, Args...);

    struct Stub
    {
        usize    size;
        StubFunc func;

        union
        {
            FuncType free_func;
            byte     functor[];

            struct
            {
                void* method;
                void* object;
            };
        };

        static R call_func(Stub* stub, Args... args)
        {
            return stub->free_func(args...);
        }

        template <typename T>
        static R call_object(void* context, Args... args)
        {
            using TMethod = R(T::*)(Args...);
            union {
                TMethod method;
                void*   callee;
            } caster;

            T* caller = *((T**)context);
            caster.callee = *((T**)context + 1); 

            return caller->*(caster.method)(args...);
        }
        
        template <typename T>
        static R call_functor(void* context, Args... args)
        {
            T* caller = (T*)context;
            return (*caller)(args...);
        }
    };

public: // 
    Stub* stub;

public:
    inline Func(FuncType func)
#if NDEBUG
        : stub((Stub*)_alloca(sizeof(Stub)))
#else
        : stub((Stub*)memory::alloc(sizeof(Stub)))
#endif
    {
        stub->size = sizeof(Stub);
        stub->func = &Stub::call_func;
        stub->free_func = func;
    }

    template <typename T>
    inline Func(T* object, R (T::*method)(Args...))
    {
    }

    template <typename T>
    inline Func(const T& functor)
    {
    }

public: // Invoking
    inline R invoke(Args... args) const
    {
        return stub->func(stub, args...);
    }

    inline R operator()(Args... args) const
    {
        return this->invoke(args...);
    }
};