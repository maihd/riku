// Copyright (c) 2019, MaiHD. All right reversed.
// License: Unlicensed

#include <zlib.h>
#include <riku/zlib.h>

namespace zlib
{
    void* zlib_alloc(void* data, uint items, uint size)
    {
        Allocator* allocator = (Allocator*)data;
        if (allocator)
        {
            return allocator->alloc((int)(items * size));
        }
        else
        {
            return memory::alloc((int)(items * size));
        }
    }

    void zlib_dealloc(void* data, void* ptr)
    {
        Allocator* allocator = (Allocator*)data;
        if (allocator)
        {
            allocator->dealloc(ptr);
        }
        else
        {
            memory::dealloc(ptr);
        }
    }

    int inflate(void* buffer, int length, const void* data, int size)
    {
        ZlibOptions options;
        options.level = 1;
        options.allocator = NULL;
        return inflate(buffer, length, data, size, options);
    }

    int deflate(void* buffer, int length, const void* data, int size)
    {
        ZlibOptions options;
        options.level = 1;
        options.allocator = NULL;
        return deflate(buffer, length, data, size, options);
    }

    int inflate(void* buffer, int length, const void* data, int size, const ZlibOptions& options)
    {
        ::z_stream stream;
        stream.zalloc = zlib_alloc;
        stream.zfree = zlib_dealloc;
        stream.opaque = options.allocator;
        int ret = inflateInit_(&stream, ZLIB_VERSION, sizeof(stream));
        if (ret != Z_OK)
        {
            return -1;
        }

        stream.avail_in = size;
        stream.avail_out = length;

        stream.next_in = (Bytef*)data;
        stream.next_out = (Bytef*)buffer;

        ret = ::inflate(&stream, Z_FINISH);
        ASSERT(ret != Z_STREAM_ERROR, "Stream data is not valid");

        inflateEnd(&stream);

        return (int)stream.total_out;
    }

    int deflate(void* buffer, int length, const void* data, int size, const ZlibOptions& options)
    {
        ::z_stream stream;
        stream.zalloc = zlib_alloc;
        stream.zfree = zlib_dealloc;
        stream.opaque = options.allocator;
        int ret = deflateInit_(&stream, options.level, ZLIB_VERSION, sizeof(stream));
        if (ret != Z_OK)
        {
            return -1;
        }

        stream.avail_in = size;
        stream.avail_out = length;

        stream.next_in = (Bytef*)data;
        stream.next_out = (Bytef*)buffer;

        ret = ::deflate(&stream, Z_FINISH);
        ASSERT(ret != Z_STREAM_ERROR, "Stream data is not valid");

        deflateEnd(&stream);

        return (int)stream.total_out;
    }
}