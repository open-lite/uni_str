#pragma once

#include <cstdint>
#include <type_traits>

#include "../include/encoding.hpp"
#include "../include/common/endian.hpp"
#include "../include/common/type_defs.hpp"


namespace oct {
	using default_uni_str_enc = UTF16<>;
}



namespace oct {
	namespace impl {
		template<typename CharTy, size_t StrSize>
		constexpr inline size_t trimmed_size(const CharTy(&str_arr)[StrSize]);
	}
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
	namespace impl {
		template <typename CharTy>
		constexpr size_t bytes_per_char() {
			return sizeof(CharTy) / sizeof(byte_t);
		}

		template <typename CharTy>
		using byte_array = std::array<byte_t, bytes_per_char<CharTy>()>;


		template<bool Endian, typename CharTy, typename... Bytes>
		using enable_if_endian = typename std::enable_if<
			bytes_per_char<CharTy>() != sizeof...(Bytes) &&
			Endian && std::is_integral<CharTy>::value,

			byte_array<CharTy>
		>::type;

		template <typename CharTy, typename... Bytes>
		using enable_if_split_complete = typename std::enable_if<
			bytes_per_char<CharTy>() == sizeof...(Bytes) &&
			std::is_integral<CharTy>::value,

			byte_array<CharTy>
		>::type;
	}


	template <typename CharTy, typename... Bytes> constexpr
	impl::enable_if_split_complete<CharTy, Bytes...> 
	split_into_bytes(CharTy /*unused*/, Bytes... bs);

	template <typename CharTy, typename... Bytes> constexpr
	impl::enable_if_endian<!oct::endian::little, CharTy, Bytes...> 
	split_into_bytes(CharTy ch, Bytes... bs);

	template <typename CharTy, typename... Bytes> constexpr
	impl::enable_if_endian<oct::endian::little, CharTy, Bytes...> 
	split_into_bytes(CharTy ch, Bytes... v);
}

#include "uni_string_internal.inl"
