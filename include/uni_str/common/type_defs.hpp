#pragma once

#include <vector>
#include <type_traits>
#include <cstdint>
#include <limits>

#include "file_versioning.hpp"
#include "cpp_defs.h"
#include "tuple_index.hpp"

#if defined(__cpp_lib_string_view) && __cpp_lib_string_view >= 201606L
#include <string_view>
#else
#include <string>
#endif



// This file is versioned because common types can be added/removed in the future
#define OL_TYPE_DEFS_MAJOR_US 1
#define OL_TYPE_DEFS_MINOR_US 2


#if  OL_TYPE_DEFS_MAJOR  < OL_TYPE_DEFS_MAJOR_US || \
	(OL_TYPE_DEFS_MAJOR == OL_TYPE_DEFS_MAJOR_US && OL_TYPE_DEFS_MINOR <= OL_TYPE_DEFS_MINOR_US)
#define OL_TYPE_DEFS_US_IS_NEWER true
#endif


#if  !defined(OL_TYPE_DEFS_MAJOR) || \
	(!defined(OL_TYPE_DEFS_DECLARED) && defined(OL_TYPE_DEFS_US_IS_NEWER))


namespace ol {
#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
	using uchar8_t = char8_t;
#else
	using uchar8_t = uint8_t;
#endif
}


namespace ol {
#if defined(__cpp_lib_string_view) && __cpp_lib_string_view >= 201606L
	template<typename CharTy>
	using str_arg = std::basic_string_view<CharTy>;
#else
	template<typename CharTy>
	using str_arg = const std::basic_string<CharTy>&;
#endif
}


namespace ol {
#if defined(__cpp_lib_byte) && __cpp_lib_byte >= 201603L
	using byte_t = std::byte;
#else
	using byte_t = uint8_t;
#endif

	template <typename CharTy>
	constexpr size_t bytes_per_char() {
		using true_char_type = typename std::decay<CharTy>::type;
		static_assert(std::is_integral<true_char_type>::value, "Cannot split non-integral type into bytes!");
		return sizeof(true_char_type) / sizeof(byte_t);
	}

	template <typename CharTy>
	using byte_array = std::array<byte_t, bytes_per_char<CharTy>()>;

	using byte_vector = std::vector<byte_t>;
}


namespace ol {
	constexpr size_t npos = -1;

	constexpr size_t nsize = std::numeric_limits<size_t>::max();
}



namespace ol {
	template<typename T>
	using remove_cvref_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;



	template<typename T>
	struct is_byte_collection : std::false_type {};

	template<>
	struct is_byte_collection<byte_vector> : std::true_type {};

	template<size_t I>
	struct is_byte_collection<std::array<byte_t, I>> : std::true_type {};

	template<typename T, typename EnableTy = bool>
	using enable_if_byte_collection = typename std::enable_if<is_byte_collection<remove_cvref_t<T>>::value, EnableTy>::type;



	template <typename T, typename = void> 
	struct is_tuple_like : std::false_type {};
	
	//Being tuple-like is defined by having a speciialization of std::tuple_size<T>
	//If it is specialized, value is defined; Otherwise, the decltype() is evaluated to void
	template <typename T> 
	struct is_tuple_like<T, decltype(std::tuple_size<remove_cvref_t<T>>::value, void())> : std::true_type {};


	template <typename T, typename EnableTy = bool>
	using enable_if_tuple_like = typename std::enable_if<is_tuple_like<T>::value, EnableTy>::type;


	template<typename T, typename TupleTy>
	struct tuple_contains : std::false_type {};

	template<typename T, typename... TupleTs>
	struct tuple_contains<T, std::tuple<TupleTs...>> : std::integral_constant<bool, (impl::tuple_index<std::tuple<TupleTs...>, T, false>::type_count != 0)> {};


	template<typename CharTy, typename EnableTy = bool>
	using enable_if_integral = typename std::enable_if<std::is_integral<CharTy>::value, EnableTy>::type;



	template<typename InputIt, typename EnableTy = bool>
	using enable_if_input_iter = typename std::enable_if<
		std::is_base_of<
			std::input_iterator_tag,
			typename std::iterator_traits<InputIt>::iterator_category
		>::value,
	EnableTy>::type;
}



#if defined(__cpp_lib_byte) && __cpp_lib_byte >= 201603L && !defined(OL_NO_BYTE_OUTPUT_OVERLOAD)
#include <iostream>
template<typename CharTy, typename Traits>
std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, std::byte b) {
	return os << std::to_integer<unsigned int>(b);
}
#endif


//File versioning boilerplate
#undef OL_TYPE_DEFS
#undef OL_TYPE_DEFS_MAJOR
#undef OL_TYPE_DEFS_MINOR

#define OL_TYPE_DEFS          OL_VERSION_STR(OL_TYPE_DEFS_MAJOR_US, OL_TYPE_DEFS_MINOR_US)
#define OL_TYPE_DEFS_MAJOR    OL_TYPE_DEFS_MAJOR_US
#define OL_TYPE_DEFS_MINOR    OL_TYPE_DEFS_MINOR_US
#define OL_TYPE_DEFS_DECLARED true

#elif defined(OL_TYPE_DEFS_US_IS_NEWER)
#pragma message(OL_OUTDATED_WARN(endian, OL_TYPE_DEFS_MAJOR, OL_TYPE_DEFS_MINOR, OL_TYPE_DEFS_MAJOR_US, OL_TYPE_DEFS_MINOR_US))
#endif