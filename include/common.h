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


//Maybe rename to US_CPP14(_CONSTEXPR)?
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201402L) || __cplusplus >= 201402L)
#define UNI_STR_CPP14 true
#define UNI_STR_CPP14_CONSTEXPR constexpr
#else 
#define UNI_STR_CPP14_CONSTEXPR
#endif



#if defined(__clang__) || defined(__GNUC__)
#define UNI_STR_PUSH_WARN_PRE_CPP14 \
_Pragma("GCC diagnostic push") \
_Pragma("GCC diagnostic ignored \"-Wpre-c++14-compat\"")

#define UNI_STR_POP_WARN \
_Pragma("GCC diagnostic pop")

#else
#define UNI_STR_PUSH_WARN_PRE_CPP14
#define UNI_STR_POP_WARN
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


namespace oct {
	template<typename CharTy, typename EnableTy = bool>
	using enable_if_char = typename std::enable_if<std::is_integral<CharTy>::value, EnableTy>::type;


	template<typename InputIt, typename EnableTy = bool>
	using enable_if_input_iter = typename std::enable_if<
		std::is_base_of<
		std::input_iterator_tag,
		typename std::iterator_traits<InputIt>::iterator_category
		>::value,
	EnableTy>::type;
}


namespace oct {
	template <typename> 
	struct is_tuple : std::false_type {};

	template <typename... Ts> 
	struct is_tuple<std::tuple<Ts...>> : std::true_type {};

	template<typename Tuple, typename EnableTy = bool>
	using enable_if_tuple = typename std::enable_if<is_tuple<Tuple>::value, EnableTy>::type;
}



namespace oct {
	namespace impl {
		template<typename CharTy, size_t StrSize>
		constexpr inline size_t trimmed_size(const CharTy(&str_arr)[StrSize]) {
			return StrSize - (StrSize > 0 && str_arr[StrSize - 1] == 0);
		}
	}
}


#if defined(UNI_STR_CPP17) && !defined(UNI_STR_NO_BYTE_OUTPUT_OVERLOAD)
#include <iostream>
template<typename CharTy, typename Traits>
std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, std::byte b) {
	return os << std::to_integer<int>(b);
}
#endif

#endif /* UNI_STR_COMMON_H */

