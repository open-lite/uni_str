#pragma once
#include <cstddef>

namespace oct {
	template<typename CharTy, typename StoreAs = CharTy>
	struct Encoding {
		using char_type = CharTy;
		using data_type = CharTy;
		using storage_type = StoreAs;

		constexpr static size_t char_size = sizeof(CharTy);
		constexpr static size_t data_size = sizeof(CharTy);
		constexpr static size_t storage_size = sizeof(StoreAs);
	};


	template <typename StoredAs = char>            
	using ASCII = Encoding<char, StoredAs>;

	template <typename StoredAs = uni_str_char8_t>
	using UTF8  = Encoding<uni_str_char8_t, StoredAs>;

	template <typename StoredAs = char16_t>
	using UTF16 = Encoding<char16_t, StoredAs>;

	template <typename StoredAs = char32_t>
	using UTF32 = Encoding<char32_t, StoredAs>;

	template<typename StoredAs = wchar_t>
	using Wide  = Encoding<wchar_t, StoredAs>;


	template<size_t target_char_size>
	struct default_encoding { 
		static_assert(target_char_size != target_char_size, "Invalid char size for type default_encoding!");
		using type = void; 
	};

	template<> struct default_encoding<1> { using type = ASCII<>; };
	template<> struct default_encoding<2> { using type = UTF16<>; };
	template<> struct default_encoding<4> { using type = UTF32<>; };

	template<size_t target_char_size>
	using default_encoding_t = typename default_encoding<target_char_size>::type;

	template<size_t target_char_size>
	using default_encoding_char_t = typename default_encoding_t<target_char_size>::char_type;


	template<typename Enc>
	using common_encoding = default_encoding_t<Enc::char_size>;


	using NativeWide = Encoding<default_encoding_char_t<sizeof(wchar_t)>, wchar_t>;
}