#pragma once

#if __GNUC__ && !__clang__
#error "riku::property: No GCC support, sorry man."
#else
#define property(getter, setter)  __declspec(property(get=getter, put=setter))
#define property_readonly(getter) __declspec(property(get=getter))
#endif