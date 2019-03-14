// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"

namespace json 
{
    /**
     * JSON type of json value
     */
    enum struct Type
    {
        Null,
        Array,
        Number,
        Object,
        String,
        Boolean,
    };

    /**
     * JSON error code
     */
    enum struct Error
    {
        None,
        
        /* Parsing error */

        WrongFormat,
        UnmatchToken,
        UnknownToken,
        UnexpectedToken,
        UnsupportedToken,

        /* Runtime error */

        OutOfMemory,
        InternalFailed,
    };

    struct State;
    struct Value;

    struct Settings
    {
        void* data;
        void* (*alloc)(void* data, usize size);
        void  (*dealloc)(void* data, void* pointer);
    };

    __rikuapi const Value& parse(const char* text, State** state = (State**)0);
    __rikuapi const Value& parse(const char* text, const Settings* settings, State** state = (State**)0);
    __rikuapi void         release(State* state);
    __rikuapi Error        get_errno(const State* state);
    __rikuapi const char*  get_error(const State* state);

    /**
     * JSON value
     */
    struct Value
    {
    public: // @region: Fields
        Type type;
        union
        {
            double      number;
            bool        boolean;

            const char* string;

            Value** array;

            struct
            {
                const char* name;
                Value*      value;
            }* object;
        };

    public: // @region: Constants
        __rikuapi static const Value NONE;

    public: // @region: Constructors
        inline Value()
            : type(Type::Null)
        {	
        }

        inline ~Value()
        {
            // SHOULD BE EMPTY
            // Memory are managed by State
        }

    public: // @region: Properties
        PROPERTY_READONLY(int, length, get_length);
        inline int get_length() const
        {
            switch (type)
            {
            case Type::Array:
                return array ? *((int*)array - 1) : 0;

            case Type::String:
                return string ? *((int*)string - 2) : 0;

            case Type::Object:
                return object ? *((int*)object - 1) : 0;

            default:
                return 0;
            }
        }
        
    public: // @region: Util methods
        __rikuapi static bool  equals(const Value& a, const Value& b);
        __rikuapi const Value& find(const char* name) const;

    public: // @region: Indexor
        inline const Value& operator[] (int index) const
        {
            if (type != Type::Array || index < 0 || index > this->get_length())
            {
                return NONE;
            }
            else
            {
                return *array[index];
            }	
        }

        inline const Value& operator[] (const char* name) const
        {
            return this->find(name);
        }

    public: // @region: Conversion
        inline operator const char* () const
        {
            return (this->type == Type::String) ? this->string : "";
        }

        inline operator double () const
        {
            return this->number;
        }

        inline operator bool () const
        {
            switch (type)
            {
            case Type::Number:
            case Type::Boolean:
            #ifdef NDEBUG
                return boolean;   // Faster, use when performance needed
            #else
                return !!boolean; // More precision, should use when debug
            #endif

            case Type::Array:
            case Type::Object:
                return true;

            case Type::String:
                return this->string && this->get_length() > 0;

            default: 
                return false;
            }
        }
    };

    inline bool operator==(const Value& a, const Value& b)
    {
        return Value::equals(a, b);
    }

    inline bool operator!=(const Value& a, const Value& b)
    {
        return !Value::equals(a, b);
    }
}