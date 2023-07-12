#pragma once
#include "common.h"
#include "encoding.h"
#include <string>
#include <vector>
#include <initializer_list>
#include <type_traits>

#ifdef UNI_STR_CPP20
#include <compare>
#endif

#ifdef UNI_STR_USE_STD_STRLEN
#define UNI_STR_STRLEN_CONSTEXPR UNI_STR_CPP17_CONSTEXPR
#else
#define UNI_STR_STRLEN_CONSTEXPR constexpr
#endif


namespace oct {
	using byte_vector = std::vector<byte_t>;


	using default_ecoding = UTF16<>;


	constexpr static size_t npos = -1;
}


namespace oct{
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
	template<class RefEncoding = default_ecoding>
	struct uni_string {
		using char_type = typename RefEncoding::char_type;
		using storage_type = typename RefEncoding::storage_type;

		UNI_STR_CPP20_CONSTEXPR
		uni_string() = default;

		//UNI_STR_CPP20_CONSTEXPR
		//virtual ~uni_string() = default;

		

		template<typename SrcEncoding> UNI_STR_CPP20_CONSTEXPR
		uni_string(uni_string<SrcEncoding> uni_str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string(str_arg<CharTy> str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> UNI_STR_CPP20_CONSTEXPR
		uni_string(const CharTy (&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string(CharTy c);

		
		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string(size_t count, CharTy c);

		template<typename InputIt, enable_if_input_iter<InputIt> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string(std::initializer_list<CharTy> char_list);
		

		template<typename SrcEncoding> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator=(uni_string<SrcEncoding> uni_str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator=(str_arg<CharTy> str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator=(const CharTy* const& str);
		
		template<typename CharTy, size_t StrSize> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator=(const CharTy(&str_arr)[StrSize]);



		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		operator std::basic_string<CharTy>() const;
		
		template<class TargetEncoding = RefEncoding> UNI_STR_CPP20_CONSTEXPR 
		std::basic_string<typename TargetEncoding::storage_type> to_str() const;


		template<typename TargetEncoding>
		explicit operator uni_string<TargetEncoding>() const;

		template<class TargetEncoding>
		uni_string<TargetEncoding> to_uni_str() const;



		UNI_STR_CPP20_CONSTEXPR bool empty() const noexcept;

		UNI_STR_CPP20_CONSTEXPR size_t size() const noexcept;
		UNI_STR_CPP20_CONSTEXPR size_t length() const noexcept;

		UNI_STR_CPP20_CONSTEXPR char_type* data() noexcept;              //marked for removal
		UNI_STR_CPP20_CONSTEXPR const char_type* data() const noexcept;	 //marked for removal
		UNI_STR_CPP20_CONSTEXPR const char_type* c_str() const noexcept; //marked for removal

		UNI_STR_CPP20_CONSTEXPR byte_vector bytes() const;


		UNI_STR_CPP20_CONSTEXPR int compare(const uni_string& str) const noexcept;


		UNI_STR_CPP20_CONSTEXPR char_type& operator[](size_t pos);             //marked for removal
		UNI_STR_CPP20_CONSTEXPR const char_type& operator[](size_t pos) const; //marked for removal
		
		UNI_STR_CPP20_CONSTEXPR char_type& at(size_t pos);			   //marked for removal
		UNI_STR_CPP20_CONSTEXPR const char_type& at(size_t pos) const; //marked for removal
		


		template<typename OtherEncoding> UNI_STR_CPP20_CONSTEXPR
		uni_string& prepend(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& prepend(str_arg<CharTy> str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& prepend(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> UNI_STR_CPP20_CONSTEXPR
		uni_string& prepend(const CharTy(&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& prepend(CharTy c);

		
		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& prepend(size_t count, CharTy c);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& prepend(str_arg<CharTy> str, size_t pos, size_t count = npos);
		
		template<typename InputIt, enable_if_input_iter<InputIt> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& prepend(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& prepend(std::initializer_list<CharTy> char_list);


		template<typename OtherEncoding> UNI_STR_CPP20_CONSTEXPR
		uni_string& append(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& append(str_arg<CharTy> str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& append(const CharTy* const& str, size_t count = nsize);

		template<typename CharTy, size_t StrSize> UNI_STR_CPP20_CONSTEXPR
		uni_string& append(const CharTy(&str_arr)[StrSize]);
		
		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& append(CharTy c);


		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& append(size_t count, CharTy c);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& append(str_arg<CharTy> str, size_t pos, size_t count = npos);
		
		template<typename InputIt, enable_if_input_iter<InputIt> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& append(InputIt srcBegin, InputIt srcEnd);

		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& append(std::initializer_list<CharTy> char_list);


		template<typename OtherEncoding> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator+=(const uni_string<OtherEncoding>& uni_str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator+=(oct::str_arg<CharTy> str);

		template<typename CharTy> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator+=(const CharTy* const& str);
		
		template<typename CharTy, size_t StrSize> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator+=(const CharTy(&str_arr)[StrSize]);

		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator+=(CharTy c);
		

		template<typename CharTy, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
		uni_string& operator+=(std::initializer_list<CharTy> char_list);



		template<typename CharTy, class Traits, class RefEnc>
		friend std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, const uni_string<RefEnc>& str);

		template<typename CharTy, class Traits, class RefEnc>
		friend std::basic_istream<CharTy, Traits>& operator>>(std::basic_istream<CharTy, Traits>& is, uni_string<RefEnc>& str);
	private:
		std::basic_string<storage_type> data_str;
	};



	//Since operator+ returns a temporary anyway, we only need two overloads, one to copy (or move if possible) lhs, and one for moving rhs
	template<class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc> lhs, const uni_string<StrEnc>& rhs);

	template<class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, uni_string<StrEnc>&& rhs);




	template<typename CharTy, class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, str_arg<CharTy> rhs);

	template<typename CharTy, class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, str_arg<CharTy> rhs);


	template<typename CharTy, class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, const CharTy* const& rhs);

	template<typename CharTy, class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, const CharTy* const& rhs);


	template<typename CharTy, class StrEnc, size_t StrSize> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, const CharTy (&rhs)[StrSize]);
	
	template<typename CharTy, class StrEnc, size_t StrSize> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, const CharTy(&rhs)[StrSize]);


	template<typename CharTy, class StrEnc, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, CharTy rhs);

	template<typename CharTy, class StrEnc, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, CharTy rhs);



	template<typename CharTy, class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(str_arg<CharTy> lhs, uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(str_arg<CharTy> lhs, const uni_string<StrEnc>& rhs);


	template<typename CharTy, class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy* const& lhs, uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy* const& lhs, const uni_string<StrEnc>& rhs);


	template<typename CharTy, class StrEnc, size_t StrSize> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy(&lhs)[StrSize], uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc, size_t StrSize> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy(&lhs)[StrSize], const uni_string<StrEnc>& rhs);


	template<typename CharTy, class StrEnc, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(CharTy lhs, uni_string<StrEnc>&& rhs);

	template<typename CharTy, class StrEnc, enable_if_char<CharTy> = true> UNI_STR_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(CharTy lhs, const uni_string<StrEnc>& rhs);

	

	template<class StrEnc> UNI_STR_CPP20_CONSTEXPR 
	bool operator==(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs);
#ifdef UNI_STR_CPP20
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
	template<typename RefEnc = default_ecoding> using UniString = uni_string<RefEnc>;
	template<typename RefEnc = default_ecoding> using uni_str = uni_string<RefEnc>;
	template<typename RefEnc = default_ecoding> using UniStr = uni_string<RefEnc>;

	using string    = uni_string<default_ecoding>;
	using String    = uni_string<default_ecoding>;

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



namespace oct {
	//Unused function
	template<typename CharTy>
	UNI_STR_STRLEN_CONSTEXPR size_t str_len(const CharTy* c_str);


	namespace impl {
		template<typename CharTy, size_t StrSize>
		constexpr inline size_t trimmed_size(const CharTy(&str_arr)[StrSize]);
	}
}



namespace oct{
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
	impl::enable_if_split_complete<CharTy, Bytes...> split_into_bytes(CharTy /*unused*/, Bytes... bs);

	template <typename CharTy, typename... Bytes> constexpr 
	impl::enable_if_endian<!oct::endian::little, CharTy, Bytes...> split_into_bytes(CharTy ch, Bytes... bs) ;

	template <typename CharTy, typename... Bytes> constexpr
	impl::enable_if_endian<oct::endian::little, CharTy, Bytes...> split_into_bytes(CharTy ch, Bytes... v);
}


#include "../src/uni_string.inl"