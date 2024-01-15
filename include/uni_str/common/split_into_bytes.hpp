#pragma once
#ifndef OL_SPLIT_INTO_BYTES
#define OL_SPLIT_INTO_BYTES

#include <utility>

#include "type_defs.hpp"
#include "integer_sequence.hpp"
#include "endian.hpp"

namespace ol {
	namespace impl {
		template <typename CharTy, size_t... Is>
		constexpr byte_array<CharTy>
		split(CharTy ch, ol::index_sequence<Is...>) {
			return { static_cast<byte_t>((ch >> (Is * 8)) & 0xFFu)... };
		}
	}
}


namespace ol {
	template <typename CharTy>
	constexpr byte_array<CharTy>
	split_into_bytes(CharTy&& ch) {
		return impl::split(std::forward<CharTy>(ch), ol::make_index_sequence<bytes_per_char<CharTy>(), endian::little>{});
	}
}


#endif