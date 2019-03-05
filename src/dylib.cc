#include <riku/dylib.h>

#if OS_WINDOWS
#include <Windows.h>
#elif OS_UNIX
#include <dlfcn.h>
#endif

namespace dylib
{
    void* open(const char* path)
    {
    #if OS_WINDOWS
        return (void*)LoadLibraryA(path);
    #elif OS_UNIX
        return dlopen(path, RTLD_LAZY | RTLD_LOCAL);
    #endif
    }

    bool close(void* handle)
    {
    #if OS_WINDOWS
        return CloseHandle((HMODULE)handle);
    #elif OS_UNIX
        return dlclose(handle) == 0;
    #endif
    }

    void* symbol(void* handle, const char* name)
    {
    #if OS_WINDOWS
        return (void*)GetProcAddress((HMODULE)handle, name);
    #elif OS_UNIX
        return dlsym(handle, name);
    #endif
    }
}