#pragma once

#include "./types.h"

#include "./str.h"
#include "./array.h"
#include "./table.h"

struct Value 
{
public:
    enum struct Type
    {
        Null,
        Number,
        String,
        Boolean,

        Array,
        Table,
    };

public:
    Type type;
    union 
    {
        double     number;
        HeapString string;  
        bool       boolean;

        Array<Value*>             array;
        Table<HeapString, Value*> table;
    };
};

struct ValuePool
{

};