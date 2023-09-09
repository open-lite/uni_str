#pragma once

#include <vector>

#include "file_versioning.hpp"
#include "cpp_defs.h"

#if defined(__cpp_lib_string_view) && __cpp_lib_string_view >= 201606L
#include <string_view>
#else
#include <string>
#endif



// This file is versioned because common types can be added/removed in the future
#define OCT_TYPE_DEFS_MAJOR_US 1
#define OCT_TYPE_DEFS_MINOR_US 0


#if  OCT_TYPE_DEFS_MAJOR  < OCT_TYPE_DEFS_MAJOR_US || \
	(OCT_TYPE_DEFS_MAJOR == OCT_TYPE_DEFS_MAJOR_US && OCT_TYPE_DEFS_MINOR <= OCT_TYPE_DEFS_MINOR_US)
#define OCT_TYPE_DEFS_US_IS_NEWER true
#endif



#if  !defined(OCT_TYPE_DEFS_MAJOR) || \
	(!defined(OCT_TYPE_DEFS_DECLARED) && defined(OCT_TYPE_DEFS_US_IS_NEWER))


namespace oct {
#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
	using uchar8_t = char8_t;
#else
	using uchar8_t = uint8_t;
#endif


#if defined(__cpp_lib_string_view) && __cpp_lib_string_view >= 201606L
	template<typename CharTy>
	using str_arg = std::basic_string_view<CharTy>;
#else
	template<typename CharTy>
	using str_arg = const std::basic_string<CharTy>&;
#endif


#if defined(__cpp_lib_byte) && __cpp_lib_byte >= 201603L
	using byte_t = std::byte;
#else
	using byte_t = uint8_t;
#endif

	using byte_vector = std::vector<byte_t>;


	constexpr size_t npos = -1;

	constexpr size_t nsize = std::numeric_limits<size_t>::max();
}


#if defined(__cpp_lib_byte) && __cpp_lib_byte >= 201603L && !defined(OCT_NO_BYTE_OUTPUT_OVERLOAD)
#include <iostream>
template<typename CharTy, typename Traits>
std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, std::byte b) {
	return os << std::to_integer<int>(b);
}
#endif



#undef OCT_TYPE_DEFS
#undef OCT_TYPE_DEFS_MAJOR
#undef OCT_TYPE_DEFS_MINOR

#define OCT_TYPE_DEFS          OCT_VERSION_STR(OCT_TYPE_DEFS_MAJOR_US, OCT_TYPE_DEFS_MINOR_US)
#define OCT_TYPE_DEFS_MAJOR    OCT_TYPE_DEFS_MAJOR_US
#define OCT_TYPE_DEFS_MINOR    OCT_TYPE_DEFS_MINOR_US
#define OCT_TYPE_DEFS_DECLARED true

#elif defined(OCT_TYPE_DEFS_US_IS_NEWER)
#pragma message(OCT_OUTDATED_WARN(endian, OCT_TYPE_DEFS_MAJOR, OCT_TYPE_DEFS_MINOR, OCT_TYPE_DEFS_MAJOR_US, OCT_TYPE_DEFS_MINOR_US))
#endif