#include "../include/uni_string.hpp"

#include <iterator>
#include <array>
#include <sstream>
#include <iomanip>


namespace oct {
	template<typename StrEnc>
	template<typename SrcEncoding> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::uni_string(oct::uni_string<SrcEncoding> src)
		: data_str(src.to_str<StrEnc>()) {}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::uni_string(str_arg<CharTy> src)
		: data_str(oct::convert<Encoding<CharTy>, StrEnc>(src)) {}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::uni_string(const CharTy* const& src, size_t count)
		: data_str(oct::convert<Encoding<CharTy>, StrEnc>(src, count)) {}

	template<typename StrEnc>
	template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::uni_string(const CharTy (&str_arr)[StrSize]) 
		: uni_string(&str_arr[0], impl::trimmed_size(str_arr)) {}

	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::uni_string(CharTy c)
		: uni_string(1, c) {}


	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::uni_string(size_t count, CharTy c)
		: data_str(oct::convert<Encoding<CharTy>, StrEnc>(std::basic_string<CharTy>(count, c))) {}

	template<typename StrEnc>
	template<typename InputIt, enable_if_input_iter<InputIt>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::uni_string(InputIt src_begin, InputIt src_end)
		: data_str(oct::convert<
			Encoding<
				default_encoding_char_t<sizeof(*(src_begin))>,
				typename std::iterator_traits<InputIt>::value_type
			>, StrEnc
		>(
			std::basic_string<typename std::iterator_traits<InputIt>::value_type>(src_begin, src_end)
		)) {}

	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::uni_string(std::initializer_list<CharTy> char_list)
		: data_str(oct::convert<Encoding<CharTy>, StrEnc>(std::data(char_list), char_list.size())) {}
}



namespace oct {
	template<typename StrEnc>
	template<typename SrcEncoding> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::operator=(uni_string<SrcEncoding> uni_str){
		data_str = uni_str.to_str<StrEnc>();
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::operator=(str_arg<CharTy> src) {
		data_str = oct::convert<Encoding<CharTy>, StrEnc>(src);
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::operator=(const CharTy* const& src) {
		data_str = oct::convert<Encoding<CharTy>, StrEnc>(src);
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::operator=(const CharTy(&str_arr)[StrSize]) {
		data_str = oct::convert<Encoding<CharTy>, StrEnc>(&str_arr[0], impl::trimmed_size(str_arr));
		return *this;
	}
}



namespace oct {
	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::operator std::basic_string<CharTy>() const {
		return to_str<Encoding<CharTy>>();
	}

	template<typename StrEnc>
	template<class TargetEncoding> OCT_CPP20_CONSTEXPR 
	std::basic_string<typename TargetEncoding::storage_type> uni_string<StrEnc>::to_str() const {
		return oct::convert<StrEnc, TargetEncoding>(data_str);
	}


	template<typename StrEnc>
	template<typename TargetEncoding> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>::operator uni_string<TargetEncoding>() const {
		return to_uni_str<TargetEncoding>();
	}

	template<typename StrEnc>
	template<class TargetEncoding> OCT_CPP20_CONSTEXPR
	uni_string<TargetEncoding> uni_string<StrEnc>::to_uni_str() const {
		return uni_string<TargetEncoding>(oct::convert<StrEnc, TargetEncoding>(data_str));
	}
}



namespace oct {
	template<typename StrEnc> OCT_CPP20_CONSTEXPR
	bool uni_string<StrEnc>::empty() const noexcept {
		return data_str.empty();
	}


	template<typename StrEnc> OCT_CPP20_CONSTEXPR
	size_t uni_string<StrEnc>::size() const noexcept {
		return data_str.size();
	}
	template<typename StrEnc> OCT_CPP20_CONSTEXPR
	size_t uni_string<StrEnc>::length() const noexcept {
		return data_str.length();
	}


	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	byte_vector uni_string<StrEnc>::bytes() const {
		using data_str_char_type = typename decltype(data_str)::value_type;

		byte_vector ret;
		ret.reserve(impl::bytes_per_char<data_str_char_type>());

		for (data_str_char_type ch : data_str) {
			impl::byte_array<data_str_char_type> bs = split_into_bytes(ch);
			ret.insert(ret.end(), bs.begin(), bs.end());
		}
		return ret;
	}
}



namespace oct {
	template<typename StrEnc> OCT_CPP20_CONSTEXPR
	int uni_string<StrEnc>::compare(const uni_string<StrEnc>& str) const noexcept {
		return data_str.compare(str.data_str);
	}
}



namespace oct {
	template<typename StrEnc>
	template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::prepend(const uni_string<OtherEncoding>& uni_str) {
		data_str.insert(0, uni_str.template to_str<StrEnc>());
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::prepend(str_arg<CharTy> str) {
		return prepend(str, 0, npos);
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::prepend(const CharTy* const& str, size_t count) {
		data_str.insert(0, oct::convert<Encoding<CharTy>, StrEnc>(str, count));
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::prepend(const CharTy(&str_arr)[StrSize]) {
		return prepend(&str_arr[0], impl::trimmed_size(str_arr));
	}

	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::prepend(CharTy c) {
		return prepend(1, c);
	}


	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::prepend(size_t count, CharTy c) {
		data_str.insert(0, oct::convert<Encoding<CharTy>, StrEnc>(std::basic_string<CharTy>(count, c)));
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::prepend(str_arg<CharTy> str, size_t pos, size_t count) {
		data_str.insert(0, oct::convert<Encoding<CharTy>, StrEnc>(str), pos, count);
		return *this;
	}

	template<typename StrEnc>
	template<typename InputIt, enable_if_input_iter<InputIt>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::prepend(InputIt src_begin, InputIt src_end) {
		data_str.insert(0, oct::convert<
			Encoding<
				default_encoding_char_t<sizeof(*(src_begin))>,
				typename std::iterator_traits<InputIt>::value_type
			>, StrEnc
		>(
			std::basic_string<typename std::iterator_traits<InputIt>::value_type>(src_begin, src_end)
		));
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::prepend(std::initializer_list<CharTy> char_list) {
		data_str.insert(0, oct::convert<Encoding<CharTy>, StrEnc>(std::data(char_list), char_list.size()));
		return *this;
	}
}


namespace oct {
	template<typename StrEnc>
	template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::append(const uni_string<OtherEncoding>& uni_str) {
		data_str.append(uni_str.template to_str<StrEnc>());
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::append(str_arg<CharTy> str) {
		return append(str, 0, npos);
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::append(const CharTy* const& str, size_t count) {
		data_str.append(oct::convert<Encoding<CharTy>, StrEnc>(str, count));
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::append(const CharTy(&str_arr)[StrSize]) {
		return append(&str_arr[0], impl::trimmed_size(str_arr));
	}

	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::append(CharTy c) {
		return append(1, c);
	}


	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::append(size_t count, CharTy c) {
		data_str.append(oct::convert<Encoding<CharTy>, StrEnc>(std::basic_string<CharTy>(count, c)));
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::append(str_arg<CharTy> str, size_t pos, size_t count) {
		data_str.append(oct::convert<Encoding<CharTy>, StrEnc>(str), pos, count);
		return *this;
	}

	template<typename StrEnc>
	template<typename InputIt, enable_if_input_iter<InputIt>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::append(InputIt src_begin, InputIt src_end) {
		data_str.append(oct::convert<
			Encoding<
				default_encoding_char_t<sizeof(*(src_begin))>,
				typename std::iterator_traits<InputIt>::value_type
			>, StrEnc
		>(
			std::basic_string<typename std::iterator_traits<InputIt>::value_type>(src_begin, src_end)
		));
		return *this;
	}

	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::append(std::initializer_list<CharTy> char_list) {
		data_str.append(oct::convert<Encoding<CharTy>, StrEnc>(std::data(char_list), char_list.size()));
		return *this;
	}
}


namespace oct {
	template<typename StrEnc>
	template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::operator+=(const uni_string<OtherEncoding>& uni_str) {
		return append(uni_str);
	}

	template<typename StrEnc>
	template<typename CharTy, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::operator+=(CharTy c) {
		return append(c);
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::operator+=(str_arg<CharTy> str) {
		return append(str);
	}

	template<typename StrEnc>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc>& uni_string<StrEnc>::operator+=(const CharTy* const& str) {
		return append(str);
	}
}



namespace oct {
	template<class CharTy, class Traits, typename StrEnc>
	std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, const uni_string<StrEnc>& str) {
		return os << str.template to_str<Encoding<CharTy>>();
	}

	template<class CharTy, class Traits, typename StrEnc>
	std::basic_istream<CharTy, Traits>& operator>>(std::basic_istream<CharTy, Traits>& is, uni_string<StrEnc>& str) {
		std::basic_string<CharTy, Traits> input;
		is >> input;
		str = input;
		return is;
	}
}



namespace oct {
	template<typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc> lhs, const uni_string<StrEnc>& rhs) {
		lhs += rhs;
		return lhs;
	}

	template<typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, uni_string<StrEnc>&& rhs) {
		uni_string<StrEnc> ret(lhs);
		return ret.append(rhs);
	}
}


namespace oct {
	template<typename CharTy, typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, str_arg<CharTy> rhs) {
		lhs += rhs;
		return lhs;
	}

	template<typename CharTy, typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, str_arg<CharTy> rhs) {
		uni_string<StrEnc> ret(lhs);
		return ret.append(rhs);
	}


	template<typename CharTy, typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, const CharTy* const& rhs) {
		lhs += rhs;
		return lhs;
	}

	template<typename CharTy, typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, const CharTy* const& rhs) {
		uni_string<StrEnc> ret(lhs);
		return ret.append(rhs);
	}


	template<typename CharTy, typename StrEnc, size_t StrSize> OCT_CPP20_CONSTEXPR
		uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, const CharTy(&rhs)[StrSize]) {
		return lhs.append(&rhs[0], impl::trimmed_size(rhs));
	}

	template<typename CharTy, typename StrEnc, size_t StrSize> OCT_CPP20_CONSTEXPR
		uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, const CharTy(&rhs)[StrSize]) {
		uni_string<StrEnc> ret(lhs);
		return ret.append(&rhs[0], impl::trimmed_size(rhs));
	}


	template<typename CharTy, typename StrEnc, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(uni_string<StrEnc>&& lhs, CharTy rhs) {
		lhs += rhs;
		return lhs;
	}
	
	template<typename CharTy, typename StrEnc, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const uni_string<StrEnc>& lhs, CharTy rhs) {
		uni_string<StrEnc> ret(lhs);
		return ret.append(rhs);
	}
}



namespace oct {
	template<typename CharTy, typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(str_arg<CharTy> lhs, uni_string<StrEnc>&& rhs) {
		return rhs.prepend(lhs);
	}

	template<typename CharTy, typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(str_arg<CharTy> lhs, const uni_string<StrEnc>& rhs) {
		uni_string<StrEnc> ret(rhs);
		return ret.prepend(lhs);
	}


	template<typename CharTy, typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy* const& lhs, uni_string<StrEnc>&& rhs) {
		return rhs.prepend(lhs);
	}

	template<typename CharTy, typename StrEnc> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy* const& lhs, const uni_string<StrEnc>& rhs) {
		uni_string<StrEnc> ret(rhs);
		return ret.prepend(lhs);
	}


	template<typename CharTy, typename StrEnc, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy(&lhs)[StrSize], uni_string<StrEnc>&& rhs) {
		return rhs.prepend(lhs);
	}

	template<typename CharTy, typename StrEnc, size_t StrSize> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(const CharTy(&lhs)[StrSize], const uni_string<StrEnc>& rhs) {
		uni_string<StrEnc> ret(rhs);
		return ret.prepend(lhs);
	}


	template<typename CharTy, typename StrEnc, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(CharTy lhs, uni_string<StrEnc>&& rhs) {
		return rhs.prepend(lhs);
	}

	template<typename CharTy, typename StrEnc, enable_if_char<CharTy>> OCT_CPP20_CONSTEXPR
	uni_string<StrEnc> operator+(CharTy lhs, const uni_string<StrEnc>& rhs) {
		uni_string<StrEnc> ret(rhs);
		return ret.prepend(lhs);
	}
}



namespace oct {
	template<typename StrEnc> OCT_CPP20_CONSTEXPR
	bool operator==(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs) {
		return lhs.compare(rhs) == 0 && lhs.size() == rhs.size();
	}

#ifdef OCT_CPP20
	template<typename StrEnc>
	constexpr std::strong_ordering operator<=>(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs) {
		return static_cast<std::strong_ordering>(lhs.compare(rhs) <=> 0);
	}
#else
	template<typename StrEnc>
	bool operator!=(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs) {
		return !(lhs == rhs);
	}

	template<typename StrEnc>
	bool operator< (const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs) {
		return lhs.compare(rhs) < 0;
	}

	template<typename StrEnc>
	bool operator> (const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs) {
		return rhs < lhs;
	}

	template<typename StrEnc>
	bool operator<=(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs) {
		return !(rhs < lhs);
	}

	template<typename StrEnc>
	bool operator>=(const uni_string<StrEnc>& lhs, const uni_string<StrEnc>& rhs) {
		return !(lhs < rhs);
	}
#endif
}



template<typename CharTy, class Traits>
std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, const oct::byte_vector& bytes) {
	os << os.widen('[');
	std::basic_ostringstream<CharTy, Traits> oss;
	oss << std::hex << std::setfill(oss.widen('0'));
	for (auto it = bytes.cbegin(); it != bytes.cend() - 1; it++)
		oss << std::uppercase << std::setw(2) << static_cast<unsigned int>(*it) << std::nouppercase << oss.widen(',') << oss.widen(' ');
	if (!bytes.empty())
		oss << std::uppercase << std::setw(2) << static_cast<unsigned int>(bytes.back()) << std::nouppercase;
	os << oss.str() << os.widen(']');
	return os;
}
