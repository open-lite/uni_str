#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include <type_traits>

#include "common/cpp_defs.h"
#include "encoding.hpp"
#include "common/endian.hpp"
#include "conversion.hpp"

#ifdef OCT_CPP20
#include <compare>
#endif
#include "../src/uni_string_internal.hpp"



namespace oct {
	template<class RefEncoding = default_uni_str_enc>
	struct uni_string {
		using char_type = typename RefEncoding::char_type;
		using storage_type = typename RefEncoding::storage_type;
		using internal_type = storage_type;

		OCT_CPP20_CONSTEXPR
		uni_string() = default;

		//OCT_CPP20_CONSTEXPR
		//virtual ~uni_string() = default;

		

		template<typename SrcEncoding> OCT_CPP20_CONSTEXPR
		uni_string(uni_string<SrcEncoding> uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string(str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		uni_string(const CharTy (&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string(CharTy c);

		
		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string(size_t count, CharTy c);

		template<typename InputIt, enable_if_input_iter<InputIt> = true> OCT_CPP20_CONSTEXPR
		uni_string(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string(std::initializer_list<CharTy> char_list);
		

		template<typename SrcEncoding> OCT_CPP20_CONSTEXPR
		uni_string& operator=(uni_string<SrcEncoding> uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& operator=(str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& operator=(const CharTy* const& str);
		
		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		uni_string& operator=(const CharTy(&str_arr)[StrSize]);



		template<typename CharTy> OCT_CPP20_CONSTEXPR
		operator std::basic_string<CharTy>() const;
		
		template<class TargetEncoding = RefEncoding> OCT_CPP20_CONSTEXPR 
		std::basic_string<typename TargetEncoding::storage_type> to_str() const;


		template<typename TargetEncoding>
		explicit operator uni_string<TargetEncoding>() const;

		template<class TargetEncoding>
		uni_string<TargetEncoding> to_uni_str() const;



		OCT_CPP20_CONSTEXPR bool empty() const noexcept;

		OCT_CPP20_CONSTEXPR size_t size() const noexcept;
		OCT_CPP20_CONSTEXPR size_t length() const noexcept;


		template<typename CharTy = internal_type> OCT_CPP20_CONSTEXPR
		byte_vector bytes() const;



		OCT_CPP20_CONSTEXPR int compare(const uni_string& str) const noexcept;
		


		template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
		uni_string& prepend(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& prepend(str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& prepend(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		uni_string& prepend(const CharTy(&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string& prepend(CharTy c);

		
		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string& prepend(size_t count, CharTy c);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& prepend(str_arg<CharTy> str, size_t pos, size_t count = npos);
		
		template<typename InputIt, enable_if_input_iter<InputIt> = true> OCT_CPP20_CONSTEXPR
		uni_string& prepend(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string& prepend(std::initializer_list<CharTy> char_list);



		template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
		uni_string& append(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& append(str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& append(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		uni_string& append(const CharTy(&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string& append(CharTy c);


		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string& append(size_t count, CharTy c);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& append(str_arg<CharTy> str, size_t pos, size_t count = npos);
		
		template<typename InputIt, enable_if_input_iter<InputIt> = true> OCT_CPP20_CONSTEXPR
		uni_string& append(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string& append(std::initializer_list<CharTy> char_list);


		template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
		uni_string& operator+=(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& operator+=(oct::str_arg<CharTy> str);

		template<typename CharTy> OCT_CPP20_CONSTEXPR
		uni_string& operator+=(const CharTy* const& str);
		
		template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
		uni_string& operator+=(const CharTy(&str_arr)[StrSize]);

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string& operator+=(CharTy c);
		

		template<typename CharTy, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
		uni_string& operator+=(std::initializer_list<CharTy> char_list);



		template<typename CharTy, class Traits, class RefEnc>
		friend std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, const uni_string<RefEnc>& str);

		template<typename CharTy, class Traits, class RefEnc>
		friend std::basic_istream<CharTy, Traits>& operator>>(std::basic_istream<CharTy, Traits>& is, uni_string<RefEnc>& str);

	private:
		std::basic_string<internal_type> data_str;
	};



	//Since operator+ returns a temporary anyway, we only need two overloads, one to copy (or move if possible) lhs, and one for moving rhs
	template<class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc> lhs, const uni_string<StrEnc>& rhs);

	template<class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, uni_string<StrEnc>&& rhs);




	template<typename CharTy, class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, str_arg<CharTy> rhs);

	template<typename CharTy, class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, str_arg<CharTy> rhs);


	template<typename CharTy, class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, const CharTy* const& rhs);

	template<typename CharTy, class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, const CharTy* const& rhs);


	template<typename CharTy, class StrEnc, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, const CharTy (&rhs)[StrSize]);
	
	template<typename CharTy, class StrEnc, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, const CharTy(&rhs)[StrSize]);


	template<typename CharTy, class StrEnc, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, CharTy rhs);

	template<typename CharTy, class StrEnc, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, CharTy rhs);



	template<typename CharTy, class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(str_arg<CharTy> lhs, uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(str_arg<CharTy> lhs, const uni_string<StrEnc>& rhs);


	template<typename CharTy, class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy* const& lhs, uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy* const& lhs, const uni_string<StrEnc>& rhs);


	template<typename CharTy, class StrEnc, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy(&lhs)[StrSize], uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy(&lhs)[StrSize], const uni_string<StrEnc>& rhs);


	template<typename CharTy, class StrEnc, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(CharTy lhs, uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc, enable_if_char<CharTy> = true> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(CharTy lhs, const uni_string<StrEnc>& rhs);

	

	template<class StrEnc> OCT_CPP20_CONSTEXPR 
	bool operator==(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs);
#ifdef OCT_CPP20
	template<class StrEnc> 
	constexpr std::strong_ordering operator<=>(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs);
#else
	template<class StrEnc>  
	bool operator!=(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs);

	template<class StrEnc>  
	bool operator< (const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs);

	template<class StrEnc>  
	bool operator> (const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs);

	template<class StrEnc>  
	bool operator<=(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs);

	template<class StrEnc>  
	
	bool operator>=(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs);
#endif



	// Type aliases for convenience
	template<typename RefEnc = default_uni_str_enc> using UniString = uni_string<RefEnc>;
	template<typename RefEnc = default_uni_str_enc> using uni_str   = uni_string<RefEnc>;
	template<typename RefEnc = default_uni_str_enc> using UniStr    = uni_string<RefEnc>;

	using string    = uni_string<default_uni_str_enc>;
	using String    = uni_string<default_uni_str_enc>;

	using astring   = uni_string<ASCII<>>;
	using wstring   = uni_string<Wide<>>;
	using u8string  = uni_string<UTF8<>>;
	using u16string = uni_string<UTF16<>>;
	using u32string = uni_string<UTF32<>>;

	//template<typename S> using uni_astring   = uni_string<ASCII<S>>;
	//template<typename S> using uni_wstring   = uni_string<Wide<S>>;
	//template<typename S> using uni_u8string  = uni_string<UTF8<S>>;
	//template<typename S> using uni_u16string = uni_string<UTF16<S>>;
	//template<typename S> using uni_u32string = uni_string<UTF32<S>>;
}


template<typename CharTy, class Traits>
std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, const oct::byte_vector& bytes);


#include "../src/uni_string.inl"