#pragma once
#include <string>
#include <vector>
#include <initializer_list>
#include <type_traits>

#include "common/cpp_defs.h"
#include "encoding.hpp"
#include "common/endian.hpp"
#include "conversion.hpp"

#ifdef OL_CPP20
#include <compare>
#endif


namespace ol { using default_uni_str_enc = UTF16<>; }


namespace ol {
	template<class RefEncoding = default_uni_str_enc>
	struct uni_string {
		using char_type = typename RefEncoding::char_type;
		using storage_type = typename RefEncoding::storage_type;
		using internal_char_type = storage_type;
		using internal_string_type = std::basic_string<internal_char_type>;

		OL_CPP20_CONSTEXPR
		uni_string() = default;

		//OL_CPP20_CONSTEXPR
		//virtual ~uni_string() = default;

		

		template<typename SrcEncoding> OL_CPP20_CONSTEXPR
		uni_string(uni_string<SrcEncoding> uni_str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string(str_arg<CharTy> str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> OL_CPP20_CONSTEXPR
		uni_string(const CharTy (&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string(CharTy c);

		
		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string(size_t count, CharTy c);

		template<typename InputIt, enable_if_input_iter<InputIt> = true> OL_CPP20_CONSTEXPR
		uni_string(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string(std::initializer_list<CharTy> char_list);
		

		template<typename SrcEncoding> OL_CPP20_CONSTEXPR
		uni_string& operator=(uni_string<SrcEncoding> uni_str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& operator=(str_arg<CharTy> str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& operator=(const CharTy* const& str);
		
		template<typename CharTy, size_t StrSize> OL_CPP20_CONSTEXPR
		uni_string& operator=(const CharTy(&str_arr)[StrSize]);



		template<typename CharTy> OL_CPP20_CONSTEXPR
		operator std::basic_string<CharTy>() const;
		
		template<class TargetEncoding = RefEncoding> OL_CPP20_CONSTEXPR 
		std::basic_string<typename TargetEncoding::storage_type> to_str() const;


		template<typename TargetEncoding> OL_CPP20_CONSTEXPR
		explicit operator uni_string<TargetEncoding>() const;

		template<class TargetEncoding> OL_CPP20_CONSTEXPR
		uni_string<TargetEncoding> to_uni_str() const;



		OL_CPP20_CONSTEXPR bool empty() const noexcept;

		OL_CPP20_CONSTEXPR size_t size() const noexcept;
		OL_CPP20_CONSTEXPR size_t length() const noexcept;


		OL_CPP20_CONSTEXPR byte_vector bytes() const;



		OL_CPP20_CONSTEXPR int compare(const uni_string& str) const noexcept;
		


		template<typename OtherEncoding> OL_CPP20_CONSTEXPR
		uni_string& prepend(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& prepend(str_arg<CharTy> str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& prepend(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> OL_CPP20_CONSTEXPR
		uni_string& prepend(const CharTy(&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string& prepend(CharTy c);

		
		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string& prepend(size_t count, CharTy c);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& prepend(str_arg<CharTy> str, size_t pos, size_t count = npos);
		
		template<typename InputIt, enable_if_input_iter<InputIt> = true> OL_CPP20_CONSTEXPR
		uni_string& prepend(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string& prepend(std::initializer_list<CharTy> char_list);



		template<typename OtherEncoding> OL_CPP20_CONSTEXPR
		uni_string& append(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& append(str_arg<CharTy> str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& append(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> OL_CPP20_CONSTEXPR
		uni_string& append(const CharTy(&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string& append(CharTy c);


		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string& append(size_t count, CharTy c);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& append(str_arg<CharTy> str, size_t pos, size_t count = npos);
		
		template<typename InputIt, enable_if_input_iter<InputIt> = true> OL_CPP20_CONSTEXPR
		uni_string& append(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string& append(std::initializer_list<CharTy> char_list);


		template<typename OtherEncoding> OL_CPP20_CONSTEXPR
		uni_string& operator+=(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& operator+=(ol::str_arg<CharTy> str);

		template<typename CharTy> OL_CPP20_CONSTEXPR
		uni_string& operator+=(const CharTy* const& str);
		
		template<typename CharTy, size_t StrSize> OL_CPP20_CONSTEXPR
		uni_string& operator+=(const CharTy(&str_arr)[StrSize]);

		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string& operator+=(CharTy c);
		

		template<typename CharTy, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
		uni_string& operator+=(std::initializer_list<CharTy> char_list);



		template<typename CharTy, class Traits, class RefEnc>
		friend std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, const uni_string<RefEnc>& str);

		template<typename CharTy, class Traits, class RefEnc>
		friend std::basic_istream<CharTy, Traits>& operator>>(std::basic_istream<CharTy, Traits>& is, uni_string<RefEnc>& str);

	private:
		internal_string_type data_str;
	};



	//Since operator+ returns a temporary anyway, we only need two overloads, one to copy (or move if possible) lhs, and one for moving rhs
	template<class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc> lhs, const uni_string<StrEnc>& rhs);

	template<class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, uni_string<StrEnc>&& rhs);




	template<typename CharTy, class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, str_arg<CharTy> rhs);

	template<typename CharTy, class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, str_arg<CharTy> rhs);


	template<typename CharTy, class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, const CharTy* const& rhs);

	template<typename CharTy, class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, const CharTy* const& rhs);


	template<typename CharTy, class StrEnc, size_t StrSize> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, const CharTy (&rhs)[StrSize]);
	
	template<typename CharTy, class StrEnc, size_t StrSize> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, const CharTy(&rhs)[StrSize]);


	template<typename CharTy, class StrEnc, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, CharTy rhs);

	template<typename CharTy, class StrEnc, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, CharTy rhs);



	template<typename CharTy, class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(str_arg<CharTy> lhs, uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(str_arg<CharTy> lhs, const uni_string<StrEnc>& rhs);


	template<typename CharTy, class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy* const& lhs, uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy* const& lhs, const uni_string<StrEnc>& rhs);


	template<typename CharTy, class StrEnc, size_t StrSize> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy(&lhs)[StrSize], uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc, size_t StrSize> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy(&lhs)[StrSize], const uni_string<StrEnc>& rhs);


	template<typename CharTy, class StrEnc, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(CharTy lhs, uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc, enable_if_integral<CharTy> = true> OL_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(CharTy lhs, const uni_string<StrEnc>& rhs);

	

	template<class StrEnc> OL_CPP20_CONSTEXPR 
	bool operator==(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs);
#ifdef OL_CPP20
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


template<typename CharTy, class Traits, typename ByteCollection, ol::enable_if_byte_collection<ByteCollection> = true>
std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, const ByteCollection& bytes);



namespace ol {
	namespace impl {
		template<typename CharTy, size_t StrSize>
		constexpr inline size_t trimmed_size(const CharTy(&str_arr)[StrSize]);
	}


	namespace impl {
		#ifdef OL_CPP20
		using std_encodings_tuple = std::tuple<ASCII<>, Wide<>, UTF16<>, UTF32<>, UTF8<>>;
		#else
		using std_encodings_tuple = std::tuple<ASCII<>, Wide<>, UTF16<>, UTF32<>>;
		#endif

		template<typename Enc, typename = void>
		struct uni_string_hash {
			std::size_t operator()(const ol::uni_string<Enc>& s) const noexcept;
		};

		template<typename Enc>
		struct uni_string_hash<Enc, typename std::enable_if<ol::tuple_contains<Enc, ol::impl::std_encodings_tuple>::value, bool>::type> {
			std::size_t operator()(const ol::uni_string<Enc>& s) const noexcept;
		};
	}
}


template<typename Enc>
struct std::hash<ol::uni_string<Enc>> {
	std::size_t operator()(const ol::uni_string<Enc>& s) const noexcept;
};




#include "../../src/uni_str.inl"