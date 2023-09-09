#pragma once
#include <tuple>
#include <string>

#include "common/cpp_defs.h"
#include "encoding.hpp"
#include "uni_string.hpp"
#include "common/tuple_index.hpp"

#include <functional>

namespace oct{
	template<typename... Encodings>
	struct multi_uni_string {
		using internal_tuple_type = std::tuple<uni_string<Encodings>...>;

		OCT_CPP20_CONSTEXPR
		multi_uni_string() = default;

		
		template<typename SrcEnc> OCT_CPP20_CONSTEXPR
		multi_uni_string(uni_string<SrcEnc> uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string(str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		multi_uni_string(const CharTy (&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string(CharTy c);


		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string(size_t count, CharTy c);

		template<typename InputIt, enable_if_input_iter<InputIt> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string(std::initializer_list<CharTy> char_list);


		
		template<typename SrcEncoding> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator=(uni_string<SrcEncoding> uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator=(str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator=(const CharTy* const& str);
		
		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator=(const CharTy(&str_arr)[StrSize]);

		

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		operator std::basic_string<CharTy>() const;
		
		template<class TargetEncoding> OCT_CPP20_CONSTEXPR 
		std::basic_string<typename TargetEncoding::storage_type> to_str() const;


		template<typename TargetEncoding>
		explicit operator uni_string<TargetEncoding>() const;

		template<class TargetEncoding>
		uni_string<TargetEncoding> to_uni_str() const;



		OCT_CPP20_CONSTEXPR bool empty() const noexcept;



		template<typename TargetEnc> OCT_CPP20_CONSTEXPR 
		byte_vector bytes() const;



		template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
		multi_uni_string& prepend(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& prepend(str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& prepend(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		multi_uni_string& prepend(const CharTy(&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& prepend(CharTy c);

		
		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& prepend(size_t count, CharTy c);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& prepend(str_arg<CharTy> str, size_t pos, size_t count = npos);
		
		template<typename InputIt, enable_if_input_iter<InputIt> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& prepend(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& prepend(std::initializer_list<CharTy> char_list);


		template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
		multi_uni_string& append(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& append(str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& append(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		multi_uni_string& append(const CharTy(&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& append(CharTy c);


		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& append(size_t count, CharTy c);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& append(str_arg<CharTy> str, size_t pos, size_t count = npos);
		
		template<typename InputIt, enable_if_input_iter<InputIt> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& append(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& append(std::initializer_list<CharTy> char_list);


		template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator+=(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator+=(oct::str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator+=(const CharTy* const& str);
		
		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator+=(const CharTy(&str_arr)[StrSize]);

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator+=(CharTy c);
		

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		multi_uni_string& operator+=(std::initializer_list<CharTy> char_list);



		template<typename CharTy, class Traits, typename... Encs>
		friend std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, const multi_uni_string<Encs...>& str);

		template<typename CharTy, class Traits, typename... Encs>
		friend std::basic_istream<CharTy, Traits>& operator>>(std::basic_istream<CharTy, Traits>& is, multi_uni_string<Encs...>& str);

	private:
		internal_tuple_type strings;


	private:
		template<typename Functor, typename... Args>
		void apply_to_each_str(Args&&... args) const;

		template<typename Functor, typename... Args>
		void apply_to_each_str(Args&&... args);
		

	private:
		template<typename Enc>
		struct contains;

		template<typename Enc> 
		OCT_CPP14_CONSTEXPR auto 
		get_internal_str() const noexcept -> typename std::enable_if<contains<Enc>::value,
			decltype(oct::get<uni_string<Enc>>(strings)) >::type;

		template<typename Enc>
		OCT_CPP14_CONSTEXPR auto
		get_internal_str() const noexcept -> typename std::enable_if<!contains<Enc>::value, 
			uni_string<Enc> >::type;
	};



	// Type aliases for convenience
	template<typename... Encs> using MultiUniString = multi_uni_string<Encs...>;
	template<typename... Encs> using multi_uni_str  = multi_uni_string<Encs...>;
	template<typename... Encs> using MultiUniStr    = multi_uni_string<Encs...>;

	using multi_string = multi_uni_string<ASCII<>, UTF8<>, UTF16<>, UTF32<>, Wide<>>;
	using MultiString  = multi_uni_string<ASCII<>, UTF8<>, UTF16<>, UTF32<>, Wide<>>;
	using multi_str    = multi_uni_string<ASCII<>, UTF8<>, UTF16<>, UTF32<>, Wide<>>;
	using MultiStr     = multi_uni_string<ASCII<>, UTF8<>, UTF16<>, UTF32<>, Wide<>>;
}



namespace oct {
	namespace impl {

		struct multi_str_empty {
			template<typename TupleStr>
			void operator()(TupleStr&& tuple_str, bool& empty) noexcept;
		};

		struct multi_str_prepend {
			template<typename TupleStr, typename... ToPrepend>
			void operator()(TupleStr&& tuple_str, ToPrepend&&... to_prepend);
		};

		struct multi_str_append {
			template<typename TupleStr, typename... ToAppend>
			void operator()(TupleStr&& tuple_str, ToAppend&&... to_append);
		};
	}
}


#include "../src/multi_string.inl"