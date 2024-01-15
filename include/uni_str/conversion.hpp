#pragma once

#include <string>
#include <type_traits>
#include <array>
#include <cstdint>

#include "common/type_defs.hpp"
#include "common/cpp_defs.h"
#include "encoding.hpp"


#ifdef UNI_STR_USE_STD_STRLEN
#define UNI_STR_STRLEN_CONSTEXPR OL_CPP17_CONSTEXPR
#else
#define UNI_STR_STRLEN_CONSTEXPR OL_CPP14_CONSTEXPR
#endif


namespace ol {
	// Internal helper functions and constants
	namespace impl {
		template <typename FromEnc, typename ToEnc>
		using enable_if_same_t = typename std::enable_if<
			std::is_same<FromEnc, ToEnc>::value,

			std::basic_string<typename ToEnc::storage_type>
		>::type;


		template <typename FromEnc, typename ToEnc>
		using enable_if_same_size_t = typename std::enable_if<
			FromEnc::char_size == ToEnc::char_size &&
			!std::is_same<FromEnc, ToEnc>::value,

			std::basic_string<typename ToEnc::storage_type>
		>::type;


		template <typename FromEnc, typename ToEnc>
		using enable_if_from_utf8_sized_t = typename std::enable_if <
			FromEnc::char_size == UTF8<>::char_size&&
			FromEnc::char_size < ToEnc::char_size,

			std::basic_string<typename ToEnc::storage_type>
		>::type;


		template <typename FromEnc, typename ToEnc>
		using enable_if_to_utf8_sized_t = typename std::enable_if <
			ToEnc::char_size == UTF8<>::char_size&&
			ToEnc::char_size < FromEnc::char_size,

			std::basic_string<typename ToEnc::storage_type>
		>::type;


		template <typename FromEnc, typename ToEnc>
		using enable_if_utf_16_to_32_t = typename std::enable_if<
			std::is_same<typename FromEnc::char_type, typename UTF16<>::char_type>::value&&
			std::is_same<typename   ToEnc::char_type, typename UTF32<>::char_type>::value,

			std::basic_string<typename ToEnc::storage_type>
		>::type;


		template <typename FromEnc, typename ToEnc>
		using enable_if_utf_32_to_16_t = typename std::enable_if<
			std::is_same<typename FromEnc::char_type, typename UTF32<>::char_type>::value&&
			std::is_same<typename   ToEnc::char_type, typename UTF16<>::char_type>::value,

			std::basic_string<typename ToEnc::storage_type>
		>::type;
	}
}


namespace ol {
	// Same exact encoding (shortcut; just returns passed variable)
	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_same_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str);

	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_same_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size);


	// Same sized encodings
	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR 
	impl::enable_if_same_size_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str);

	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_same_size_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size);
	

	// Single byte to higher encodings
	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_from_utf8_sized_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str);

	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_from_utf8_sized_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size);


	// Higher encodings to single byte
	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_to_utf8_sized_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str);

	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_to_utf8_sized_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size);


	// From UTF-16 to UTF-32
	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_utf_16_to_32_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str);

	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_utf_16_to_32_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size);

	
	// From UTF-32 to UTF-16
	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_utf_32_to_16_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str);

	template<typename FromEnc, typename ToEnc> OL_CPP20_CONSTEXPR
	impl::enable_if_utf_32_to_16_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size);
}


namespace ol {

	using unicode_cp_t = int32_t;


	namespace impl {
		constexpr size_t unicode_short_stackbuf_size = (64 - sizeof(void*) - 2) / 2;
		constexpr ol::unicode_cp_t utf16_surrogate_offset = ((0xD800 << 10UL) + 0xDC00 - 0x10000);
		constexpr ol::unicode_cp_t utf16_trail_surrogate_offset = (0xD800 - (0x10000 >> 10));
		constexpr uint32_t replacement_char = 0xFFFD;


		constexpr inline ol::UTF16<>::char_type lead_surrogate(ol::unicode_cp_t code_point) noexcept;
		constexpr inline ol::UTF16<>::char_type trail_surrogate(ol::unicode_cp_t code_point) noexcept;
	}


	namespace impl {
		template <typename Enc>
		struct surrogate_arr { using type = std::array<typename Enc::storage_type, 1>; };

		template<typename StorageTy>
		struct surrogate_arr<ol::UTF16<StorageTy>> { using type = std::array<StorageTy, 2>; };

		template <typename Enc>
		using surrogate_arr_t = typename surrogate_arr<Enc>::type;


		template<typename Enc>
		struct utf {
			template<typename... UTF16Args>
			constexpr static inline ol::unicode_cp_t supplementary_code_point(ol::unicode_cp_t code_point, UTF16Args...);

			constexpr static inline surrogate_arr_t<Enc> surrogates(ol::unicode_cp_t code_point);

			template<typename... UTF16Args>
			constexpr static inline bool is_supplementary_plane(ol::unicode_cp_t cp, UTF16Args...);
		};

		template<typename StorageTy>
		struct utf<ol::UTF16<StorageTy>> {
			constexpr static inline ol::unicode_cp_t supplementary_code_point(ol::unicode_cp_t code_point, uint32_t trail);

			constexpr static inline surrogate_arr_t<ol::UTF16<StorageTy>> surrogates(ol::unicode_cp_t code_point);

			constexpr static inline bool is_supplementary_plane(ol::unicode_cp_t cp, uint32_t& trail, const StorageTy* src_str, size_t& i, size_t src_size);
		};
	}



	namespace impl {
		template<typename CharTy> UNI_STR_STRLEN_CONSTEXPR
			size_t str_len(const CharTy* str);

		template <typename Enc>
		constexpr inline size_t capacity_for(const typename Enc::storage_type* str, size_t size);
	}
}

#include "../../src/conversion.inl"