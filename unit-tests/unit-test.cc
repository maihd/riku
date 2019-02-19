#include "./unit-test.h"

UnitTest* UnitTest::root = nullptr;

int main()
{
    UnitTest* test = UnitTest::root;
    while (test)
    {
        test->execute();
        test = test->next;   
    }

    return 0;
}