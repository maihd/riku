#pragma once

#include <riku.h>

struct UnitTest
{
    UnitTest* next;
    static UnitTest* root;

    inline UnitTest()
    {
        this->next = nullptr;
        if (UnitTest::root)
        {
            UnitTest::root = UnitTest::root->next = this;
        }
        else
        {
            UnitTest::root = this;
        }
    }

    virtual void execute() = 0;
};