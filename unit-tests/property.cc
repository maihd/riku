#include <stdio.h>

#include "../include/riku/property.h"

struct PropertyTest
{
public:
    property(int, get_value, set_value) value;
    
public:
    int get_value()
    {
        return _value;
    }

    void set_value(int v)
    {
        _value = v;
    }

private: // Use private only for this feature, donot use in real-life code
    int _value;
};

int main()
{
    PropertyTest test;
    test.value = 0;
    printf("test.value = %d\n", test.value);

    test.value = 1;
    printf("test.value = %d\n", test.value);

    test.value = 1;
    printf("test.value = %d\n", test.value);

    test.value = 2;
    printf("test.value = %d\n", test.value);

    test.value = 3;
    printf("test.value = %d\n", test.value);

    test.value = 4;
    printf("test.value = %d\n", test.value);

    test.value = 5;
    printf("test.value = %d\n", test.value);

    test.value = 6;
    printf("test.value = %d\n", test.value);

    test.value = 7;
    printf("test.value = %d\n", test.value);

    test.value = 8;
    printf("test.value = %d\n", test.value);

    test.value = 9;
    printf("test.value = %d\n", test.value);

    return 0;
}