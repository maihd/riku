#pragma once

#include "./core.h"

namespace fs
{
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
    RIKU_API bool  exists(const String& path);
}