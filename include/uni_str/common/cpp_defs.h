#pragma once


#undef OCT_CPP20
#undef OCT_CPP20_CONSTEXPR
#undef OCT_CPP17
#undef OCT_CPP17_CONSTEXPR
#undef OCT_CPP14
#undef OCT_CPP14_CONSTEXPR
#undef OCT_PUSH_WARN_PRE_CPP14
#undef OCT_POP_WARN



#if((defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || __cplusplus >= 202002L)
#define OCT_CPP20 true
#define OCT_CPP20_CONSTEXPR constexpr
#else 
#define OCT_CPP20_CONSTEXPR
#endif


//Maybe rename to US_CPP17(_CONSTEXPR)?
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#define OCT_CPP17 true
#define OCT_CPP17_CONSTEXPR constexpr
#include <cstddef>
#else 
#define OCT_CPP17_CONSTEXPR
#endif


//Maybe rename to US_CPP14(_CONSTEXPR)?
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201402L) || __cplusplus >= 201402L)
#define OCT_CPP14 true
#define OCT_CPP14_CONSTEXPR constexpr
#else 
#define OCT_CPP14_CONSTEXPR
#endif



#if defined(__clang__) || defined(__GNUC__)
#define OCT_PUSH_WARN_PRE_CPP14 \
_Pragma("GCC diagnostic push") \
_Pragma("GCC diagnostic ignored \"-Wpre-c++14-compat\"")

#define OCT_POP_WARN \
_Pragma("GCC diagnostic pop")

#else
#define OCT_PUSH_WARN_PRE_CPP14
#define OCT_POP_WARN
#endif