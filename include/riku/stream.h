#pragma once

#include "./core.h"

struct StreamWritable
{
public:
    int write(const void* data, int size) {}
};

struct StreamReadable 
{
public:
    int read(void* data, int size) {}
};

struct StreamDuplex : public StreamReadable, public StreamWritable
{
};

struct StreamTransform : public StreamDuplex
{
};