#pragma once

#if __GNUC__ && !__clang__
#error "riku::property: No GCC support, sorry man."
#else
#define propdef(getter, setter)   __declspec(property(get=getter, put=setter))
#define propdef_readonly(getter)  __declspec(property(get=getter))
#define propdef_writeonly(setter) __declspec(property(put=setter))
#endif