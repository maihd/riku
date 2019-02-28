#pragma once

#include "./core.h"

namespace fs
{
#if 0 && PREVIEWING
    enum struct FileType
    {
        None,
        File,
        Directory,
    };

    struct Stats
    {
        FileType type;
    };

    RIKU_API Stats stat(const String& path);
#endif
    
    RIKU_API bool   exists(const String& path);
    RIKU_API Buffer read_file(const String& path);
}