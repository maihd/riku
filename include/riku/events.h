#pragma once

#include "./core.h"
#include "./list.h"
#include "./dictionary.h"

// EventEmitter: High-level event emitter. An alternative for C# multicast delegate.
template <typename TFunc, typename TName = int>
struct EventEmitter
{
public:
    Dictionary<TName, List<TFunc>> entries; 
    Dictionary<TName, List<TFunc>> once_entries;

public:
    bool on(const TName& name, const TFunc& func)
    {
        List<TFunc>& listeners = entries[name];
        return listeners.push(func);
    }

    bool off(const TName& name, const TFunc& func)
    {
        List<TFunc>& listeners = entries[name];
        if (listeners.remove(func))
        {
            return true;
        }

        List<TFunc>& once_listeners = entries[name];
        if (listeners.remove(func))
        {
            return true;
        }

        return false;
    }

    bool once(const TName& name, const TFunc& func)
    {
        List<TFunc>& once_listeners = entries[name];
        return listeners.push(func);
    }

    template <typename... TArgs>
    bool emit(const TName& name, TArgs... args) const
    {
        bool result = false;

        const List<TFunc>& listeners = entries[name];
        for (int i = 0, n = listeners.length; i < n; i++)
        {
            listeners[i](args...);
            result = true;
        }

        List<TFunc>& once_listeners = (List<TFunc>&)once_entries[name];
        for (int i = 0, n = once_listeners.length; i < n; i++)
        {
            once_listeners[i](args...); 
            result = true;
        }

        // Remove all listeners that emit once time only
        once_listeners.clear();

        // Has any listeners called
        return result;
    } 
};