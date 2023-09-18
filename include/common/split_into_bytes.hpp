#pragma once
#ifndef OCT_SPLIT_INTO_BYTES
#define OCT_SPLIT_INTO_BYTES

#include <utility>

#include "type_defs.hpp"
#include "integer_sequence.hpp"
#include "endian.hpp"

namespace oct {
	namespace impl {
		template <typename CharTy, size_t... Is>
		constexpr byte_array<CharTy>
		split(CharTy ch, oct::index_sequence<Is...>) {
			return { static_cast<byte_t>((ch >> (Is * 8)) & 0xFFu)... };
		}
	}
}


namespace oct {
	template <typename CharTy>
	constexpr byte_array<CharTy>
	split_into_bytes(CharTy&& ch) {
		return impl::split(std::forward<CharTy>(ch), oct::make_index_sequence<bytes_per_char<CharTy>(), endian::little>{});
	}
}


#endif