#include "uni_string_internal.hpp"


namespace oct {
	namespace impl {
		template<typename CharTy, size_t StrSize>
		constexpr size_t trimmed_size(const CharTy(&str_arr)[StrSize]) {
			return StrSize - (StrSize > 0 && str_arr[StrSize - 1] == 0);
		}
	}
}



namespace oct {
	template <typename CharTy, typename... Bytes> constexpr
	impl::enable_if_split_complete<CharTy, Bytes...> split_into_bytes(CharTy /*unused*/, Bytes... bs) {
		return { static_cast<byte_t>(bs)... };
	}

	template <typename CharTy, typename... Bytes> constexpr
	impl::enable_if_endian<!oct::endian::little, CharTy, Bytes...> split_into_bytes(CharTy ch, Bytes... bs) {
		//return split_into_bytes<CharTy, CharTy, Vals...>(ch, v..., (sizeof...(Vals)));
		return split_into_bytes<CharTy, Bytes..., CharTy>(ch, bs..., ((ch >> ((sizeof...(Bytes)) * 8)) & 0xFFu));
	}

	template <typename CharTy, typename... Bytes> constexpr
	impl::enable_if_endian<oct::endian::little, CharTy, Bytes...> split_into_bytes(CharTy ch, Bytes... v) {
		//return split_into_bytes<CharTy, CharTy, Vals...>(ch, (sizeof...(Vals)), v...);
		return split_into_bytes<CharTy, CharTy, Bytes...>(ch, ((ch >> ((sizeof...(Bytes)) * 8)) & 0xFFu), v...);
	}
}