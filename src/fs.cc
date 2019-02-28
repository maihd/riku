#include <stdio.h>
#include <riku/fs.h>

namespace fs
{
    bool exists(const String& path)
    {
        FILE* file = fopen(path.buffer, "r");
        if (file)
        {
            fclose(file);
            return true;
        }
        else
        {
            return false;
        }
    }
}