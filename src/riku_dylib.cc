#include <riku/dylib.h>

#if PLATFORM_WINDOWS
#include <Windows.h>
#elif PLATFORM_UNIX
#include <dlfcn.h>
#endif

namespace dylib
{
    void* open(const char* path)
    {
    #if PLATFORM_WINDOWS
        return (void*)LoadLibraryA(path);
    #elif PLATFORM_UNIX
        return dlopen(path, RTLD_LAZY | RTLD_LOCAL);
    #endif
    }

    bool close(void* handle)
    {
    #if PLATFORM_WINDOWS
        return CloseHandle((HMODULE)handle);
    #elif PLATFORM_UNIX
        return dlclose(handle) == 0;
    #endif
    }

    void* symbol(void* handle, const char* name)
    {
    #if PLATFORM_WINDOWS
        return (void*)GetProcAddress((HMODULE)handle, name);
    #elif PLATFORM_UNIX
        return dlsym(handle, name);
    #endif
    }
}