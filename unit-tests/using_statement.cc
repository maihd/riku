// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include "./unit_test.h"

// Using like typedef
struct SomeStruct
{
    using ValueType = int;  
};

SomeStruct::ValueType some_value = 10;