#include <riku/core.h>
#include <riku/alloc.h>

struct AllocHeader
{
    int          size;
    AllocHeader* prev;
};

void* StackAllocator::alloc(int size, int align)
{
    int total_size = sizeof(AllocHeader) + size + align;
    if (allocated + total_size <= buffer.get_length())
    {
        AllocHeader* header = (AllocHeader*)(buffer.data + allocated);
        header->size = size + align;
        header->prev = (AllocHeader*)last_block;
        last_block = header;
        
        void* result = header + 1;
        allocated += total_size;
        return memory::align(result, align);
    }
    else
    {
        return NULL;
    }
}

void* StackAllocator::realloc(void* ptr, int size, int align)
{
    if (ptr)
    {
        AllocHeader* real_block = (AllocHeader*)((byte*)memory::dealign(ptr) - sizeof(AllocHeader));
        if (last_block == real_block)
        {
            allocated += (size + align) - (real_block->size);
            return memory::align(real_block + 1, align);
        }
    }

    return alloc(size, align);
}

void StackAllocator::dealloc(void* ptr)
{
    if (ptr)
    {
        AllocHeader* real_block = (AllocHeader*)((byte*)memory::dealign(ptr) - sizeof(AllocHeader));
        if (last_block == real_block)
        {
            allocated -= real_block->size;
            last_block = real_block->prev;
        }
    }
}

void* LinearAllocator::alloc(int size, int align)
{
    int total_size = sizeof(AllocHeader) + size + align;
    if (allocated + total_size <= buffer.get_length())
    {
        void* result = (AllocHeader*)(buffer.data + allocated);
        allocated += total_size;
        return memory::align(result, align);
    }
    else
    {
        return NULL;
    }
}

void* LinearAllocator::realloc(void* ptr, int size, int align)
{
    (void)ptr;
    return alloc(size, align);
}

void  LinearAllocator::dealloc(void* ptr)
{
    (void)ptr;
}

void PoolAllocator::clear(void)
{
    buffers.unref();
    free_handles.unref();
}

void* PoolAllocator::acquire(int count)
{
    if (free_handles.get_length() > 0)
    {
        void* handle = free_handles.pop();
        return handle;
    }
    else
    {
        for (int i = 0, n = buffers.get_length(); i < n; i++)
        {
            Array<byte>& buffer = buffers[i];
            if (buffer.get_capacity() && buffer.get_length() + count <= buffer.get_capacity())
            {
                int index = buffer.get_length() - 1;
                buffer.buffer->length += count;
                return &buffer[index];
            }
        }

        Array<byte> buffer = Array<byte>(allocator);
        if (buffer.grow(bucket_size * block_size))
        {
            buffers.push(buffer);

            int index = buffer.get_length() - 1;
            buffer.buffer->length += count;
            return &buffer[index];
        }

        return NULL;
    }
}

bool PoolAllocator::release(void* ptr)
{
    for (int i = 0, n = buffers.get_length(); i < n; i++)
    {
        Array<byte>& buffer = buffers[i];
        byte* container = buffer.get_items();
        if (container && ptr >= container && ptr <= container + bucket_size * block_size)
        {
            free_handles.push(ptr);
            return true;
        }
    }

    return false;
}