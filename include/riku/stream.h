#pragma once

#include "./core.h"

struct StreamWritable
{
public:
    int write(const void* data, int size) 
    {
        (void)data;
        (void)size;
        return -1;
    }
};

struct StreamReadable 
{
public:
    int read(void* data, int size) 
    {
        (void)data;
        (void)size;
        return -1;
    }
};

struct StreamDuplex : public StreamReadable, public StreamWritable
{
};

struct StreamTransform : public StreamDuplex
{
};