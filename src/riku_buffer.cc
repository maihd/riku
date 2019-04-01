#include <riku/core.h>
#include <riku/buffer.h>

Buffer Buffer::alloc(int length)
{
    Buffer buf;
    if (length)
    {
        buf.data = (byte*)memory::alloc(sizeof(int) + length);
        *(int*)buf.data = length;
        buf.data += sizeof(int);
    }
    return traits::make_rvalue(buf);
}