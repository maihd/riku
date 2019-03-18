// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

template <typename T>
struct Func;

template <typename R, typename ...Args>
struct Func<R(Args...)>
{
public:
    struct Stub;

    using FuncType = R(*)(Args...);
    using StubFunc = R(*)(Stub* stub, Args...);

    enum struct Type
    {
        Method,
        Functor,
        Function,
    };

    struct Stub : RefCount
    {
        Type     type;
        StubFunc func;

        union
        {
            FuncType free_func;

            struct
            {
                usize size;
                byte  functor[sizeof(FuncType)];
            };

            struct
            {
                void* object;
                void* method;
            };
        };

        static R call_func(Stub* stub, Args... args)
        {
            return stub->free_func(args...);
        }

        template <typename T>
        static R call_object(Stub* stub, Args... args)
        {
            using TMethod = R(T::*)(Args...);
            union {
                TMethod method;
                void*   callee;
            } caster;

            T* caller = (T*)stub->object;
            caster.callee = stub->method; 
            return (caller->*caster.method)(args...);
        }
        
        template <typename T>
        static R call_functor(Stub* stub, Args... args)
        {
            const T* functor = (T*)stub->functor;
            return (*functor)(args...);
        }
    };

public: // 
    Stub* stub;

public:
    constexpr Func(void)
        : stub(NULL)
        {}

    constexpr Func(NullPtr)
        : stub(NULL)
        {}
    
    inline ~Func(void)
    {
        if (stub && stub->_ref_dec() <= 0)
        {
            memory::dealloc(stub);
        }
    }

public:
    inline Func(FuncType func)
        : stub((Stub*)memory::alloc(sizeof(Stub)))
    {
        INIT(stub) RefCount();

        stub->type      = Type::Function;
        stub->func      = &Stub::call_func;
        stub->free_func = func;
    }

    template <typename T>
    inline Func(T* object, R (T::*method)(Args...))
        : stub((Stub*)memory::alloc(sizeof(Stub)))
    {
        INIT(stub) RefCount();

        using TMethod = R(T::*)(Args...);
        union 
        {
            TMethod method;
            void*   pointer;
        } caster;
        caster.method = method;

        stub->type   = Type::Method;
        stub->func   = &Stub::template call_object<T>;
        stub->object = object;
        stub->method = caster.pointer;
    }

    template <typename T>
    inline Func(const T& functor)
        : stub((Stub*)memory::alloc(sizeof(Stub) + (sizeof(functor))))
    {
        INIT(stub) RefCount();

        stub->type = Type::Functor;
        stub->size = sizeof(Stub) + sizeof(functor);
        stub->func = &Stub::template call_functor<T>;

        memory::copy(stub->functor, &functor, sizeof(functor));
    }

public:
    inline Func& assign(NullPtr)
    {
        // unref old stub
        this->~Func();

        // Create new stub
        stub = NULL;

        return *this;
    }

    inline Func& assign(FuncType func)
    {
        // unref old stub
        this->~Func();

        // Create new stub
        stub = (Stub*)memory::alloc(sizeof(Stub)); 
        INIT(stub) RefCount();

        stub->type      = Type::Function;
        stub->func      = &Stub::call_func;
        stub->free_func = func;

        return *this;
    }

    template <typename T>
    inline Func& assign(T* object, R(T::*method)(Args...))
    {
        // unref old stub
        this->~Func();

        // Create new stub
        stub = (Stub*)memory::alloc(sizeof(Stub)); 
        INIT(stub) RefCount();

        using TMethod = R(T::*)(Args...);
        union
        {
            TMethod method;
            void*   pointer;
        } caster;
        caster.method = method;

        stub->type   = Type::Method;
        stub->func   = &Stub::template call_object<T>;
        stub->object = object;
        stub->method = caster.pointer;

        return *this;
    }

    template <typename T>
    inline Func& assign(const T& functor)
    {
        // unref old stub
        this->~Func();

        // Create new stub
        stub = (Stub*)memory::alloc(sizeof(Stub) + (sizeof(functor)));
        INIT(stub) RefCount();

        stub->type = Type::Functor;
        stub->size = sizeof(Stub) + sizeof(functor);
        stub->func = &Stub::template call_functor<T>;

        memory::copy(stub->functor, &functor, sizeof(functor));

        return *this;
    }

public:
    inline Func& operator=(NullPtr)
    {
        return this->assign(NullPtr());
    }

    inline Func& operator=(FuncType func)
    {
        return this->assign(func);
    }

    template <typename T>
    inline Func& operator=(const T& functor)
    {
        return this->assign(functor);
    }

public:
    inline Func(const Func& other)
    {
        stub = other.stub;
        if (stub)
        {
            stub->_ref_inc();
        }
    }

    inline Func& operator=(const Func& other)
    {
        // unref old stub
        this->~Func();
        
        stub = other.stub;
        if (stub)
        {
            stub->_ref_inc();
        }

        return *this;
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

public: // Operators 
    inline operator bool() const
    {
        return stub != NULL;
    } 
};

template <typename R, typename ...Args>
inline bool operator==(const Func<R(Args...)>& a, const Func<R(Args...)>& b)
{
    using Type = typename Func<R(Args...)>::Type;

    if (a.stub == b.stub)
    {
        return true;
    }

    if (!a.stub || !b.stub)
    {
        return false;
    }

    if (a.stub->type != b.stub->type)
    {
        return false;
    }

    switch (a.stub->type)
    {
    case Type::Function:
        return a.stub->free_func == b.stub->free_func;

    case Type::Method:
        return a.stub->object == b.stub->object && a.stub->method == b.stub->method;

    case Type::Functor:
        if (a.stub->size != b.stub->size)
        {
            return false;
        }
        else
        {
            return memory::compare(a.stub, b.stub, a.stub->size) == 0;
        }
    }

    return false; // Satisfy the compiler
}

template <typename R, typename ...Args>
inline bool operator!=(const Func<R(Args...)>& a, const Func<R(Args...)>& b)
{
    using Type = typename Func<R(Args...)>::Type;

    if (a.stub == b.stub)
    {
        return false;
    }

    if (!a.stub || !b.stub)
    {
        return true;
    }

    if (a.stub->type != b.stub->type)
    {
        return true;
    }

    switch (a.stub->type)
    {
    case Type::Function:
        return a.stub->free_func != b.stub->free_func;

    case Type::Method:
        return a.stub->object != b.stub->object || a.stub->method != b.stub->method;

    case Type::Functor:
        if (a.stub->size != b.stub->size)
        {
            return true;
        }
        else
        {
            return memory::compare(a.stub, b.stub, a.stub->size) != 0;
        }
    }

    return true; // Satisfy the compiler
}

template <typename R, typename ...Args>
inline bool operator==(const Func<R(Args...)>& a, NullPtr)
{
    return !((bool)a);
}

template <typename R, typename ...Args>
inline bool operator==(NullPtr, const Func<R(Args...)>& b)
{
    return !((bool)b);
}

template <typename R, typename ...Args>
inline bool operator!=(const Func<R(Args...)>& a, NullPtr)
{
    return ((bool)a);
}

template <typename R, typename ...Args>
inline bool operator!=(NullPtr, const Func<R(Args...)>& b)
{
    return ((bool)b);
}

template <typename T, typename R, typename ... Args>
inline Func<R(Args...)> make_func(T* object, R(T::*method)(Args...))
{
    return Func<R(Args...)>(object, method);
}