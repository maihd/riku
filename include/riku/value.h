#pragma once

#include "./core.h"
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
        String string;  
        bool       boolean;

        Array<Value*>             array;
        Table<String, Value*> table;
    };
};

struct ValuePool
{

};