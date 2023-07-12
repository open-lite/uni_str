#pragma once
#ifndef UNI_STR_COMMON_H
#define UNI_STR_COMMON_H

//#include "export_defs.h"
#include <cstdint>
#include <string>


//Maybe rename to US_CPP20(_CONSTEXPR)?
#if((defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || __cplusplus >= 202002L)
#define UNI_STR_CPP20 true
#define UNI_STR_CPP20_CONSTEXPR constexpr
#else 
#define UNI_STR_CPP20_CONSTEXPR
#endif


//Maybe rename to US_CPP17(_CONSTEXPR)?
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
#define UNI_STR_CPP17 true
#define UNI_STR_CPP17_CONSTEXPR constexpr
#include <string_view>
#include <cstddef>
#else 
#define UNI_STR_CPP17_CONSTEXPR
#endif


namespace oct {
#ifdef UNI_STR_CPP20
	using uni_str_char8_t = char8_t;
#else
	using uni_str_char8_t = uint8_t;
#endif


#ifdef UNI_STR_CPP17
	template<typename CharTy>
	using str_arg = std::basic_string_view<CharTy>;

	using byte_t = std::byte;
#else
	template<typename CharTy>
	using str_arg = const std::basic_string<CharTy>&;

	using byte_t = uint8_t;
#endif

	
	using unicode_cp_t = int32_t;
}


#ifndef OCT_ENDIAN
#define OCT_ENDIAN
namespace oct {
	namespace endian {
		namespace impl {
			constexpr uint32_t test_u32  = 0x01020304;
			constexpr uint8_t  test_byte = (const uint8_t&)test_u32;
		}

		constexpr bool little = impl::test_byte == 0x4;
		constexpr bool big    = impl::test_byte == 0x1;
	}
}
#endif



#if defined(UNI_STR_CPP17) && !defined(UNI_STR_NO_BYTE_OUTPUT_OVERLOAD)
#include <iostream>
template<typename CharTy, typename Traits>
std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, std::byte b) {
	return os << std::to_integer<int>(b);
}
#endif

#endif /* UNI_STR_COMMON_H */

