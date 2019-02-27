#include <riku/define.h>

// Using like typedef
struct SomeStruct
{
    using ValueType = int;  
};

SomeStruct::ValueType some_value = 10;