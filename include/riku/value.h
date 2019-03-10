// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#pragma once

#include "./core.h"
#include "./array.h"
#include "./hash_table.h"

enum struct ValueType
{
    Null,
    Number,
    String,
    Boolean,

    Array,
    Table,
};

struct Value 
{
public:
    ValueType type;
    union 
    {
        double      number;
        const char* string;  
        bool        boolean;

        Array<Value*>     array;
        HashTable<Value*> table;
    };
};

struct ValuePool
{

};