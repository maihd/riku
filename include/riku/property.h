#pragma once

#if __GNUC__ && !__clang__
#error "riku::property: No GCC support, sorry man."
#else
#define property(type, getter, setter)  __declspec(property(get=getter, put=setter)) type
#define property_readonly(type, getter) __declspec(property(get=getter)) type
#endif