#pragma once

#include "./core.h"
#include "./list.h"
#include "./dictionary.h"

// EventEmitter: High-level event emitter. An alternative for C# multicast delegate.
template <typename TName, typename TFunc>
struct EventEmitter;

// EventEmitter: High-level event emitter. An alternative for C# multicast delegate.
template <typename TName, typename TFunc>
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
        List<TFunc>& once_listeners = once_entries[name];
        return once_listeners.push(func);
    }

    template <typename... TArgs>
    uint emit(const TName& name, TArgs... args) const
    {
        uint result = 0;

        List<TFunc> listeners = entries[name];
        for (int i = 0, n = listeners.get_length(); i < n; i++, result++)
        {
            listeners[i](args...);
        }

        List<TFunc> once_listeners = once_entries[name];
        for (int i = 0, n = once_listeners.get_length(); i < n; i++, result++)
        {
            once_listeners[i](args...); 
        }

        // Remove all listeners that emit once time only
        once_listeners.clear();

        // Has any listeners called
        return result;
    } 
};