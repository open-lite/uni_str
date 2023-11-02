#include "../include/multi_string.hpp"

#include "common/apply.hpp"

#include <functional>



#define ASSERT_VALID_ENC(enc) static_assert(multi_string_contains<multi_uni_string<Encs...>, enc>::value, "multi_uni_string does not contain given encoding!");

namespace oct {
	template<typename... Encs>
	template<typename SrcEnc> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::multi_uni_string(uni_string<SrcEnc> uni_str)
		: strings(std::make_tuple(uni_str.to_uni_str<Encs>()...)) {}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::multi_uni_string(str_arg<CharTy> src)
		: strings(std::make_tuple(uni_string<Encs>(src)...)) {}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::multi_uni_string(const CharTy* const& src, size_t count)
		: strings(std::make_tuple(uni_string<Encs>(src, count)...)) {}

	template<typename... Encs>
	template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::multi_uni_string(const CharTy(&str_arr)[StrSize])
		: multi_uni_string(&str_arr[0], impl::trimmed_size(str_arr)) {}

	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::multi_uni_string(CharTy c)
		: multi_uni_string(1, c) {}


	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::multi_uni_string(size_t count, CharTy c)
		: strings(std::make_tuple(uni_string<Encs>(count, c)...)) {}

	template<typename... Encs>
	template<typename InputIt, enable_if_input_iter<InputIt>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::multi_uni_string(InputIt src_begin, InputIt src_end)
		: strings(std::make_tuple(uni_string<Encs>(src_begin, src_end)...)) {}

	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::multi_uni_string(std::initializer_list<CharTy> char_list)
		: strings(std::make_tuple(uni_string<Encs>(char_list)...)) {}
}



namespace oct {
	template<typename... Encs>
	template<typename SrcEnc> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::operator=(uni_string<SrcEnc> uni_str) {
		strings = std::make_tuple(uni_str.to_uni_str<Encs>()...);
		return *this;
	}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::operator=(str_arg<CharTy> src) {
		strings = std::make_tuple(uni_string<Encs>(src)...);
		return *this;
	}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::operator=(const CharTy* const& src) {
		strings = std::make_tuple(uni_string<Encs>(src)...);
		return *this;
	}

	template<typename... Encs>
	template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::operator=(const CharTy(&str_arr)[StrSize]) {
		strings = std::make_tuple(uni_string<Encs>(&str_arr[0], impl::trimmed_size(str_arr))...);
		return *this;
	}
}



namespace oct {
	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::operator std::basic_string<CharTy>() const {
		return to_str<Encoding<CharTy>>();
	}

	template<typename... Encs>
	template<class TargetEnc> OCT_CPP20_CONSTEXPR 
	std::basic_string<typename TargetEnc::storage_type> multi_uni_string<Encs...>::to_str() const {
		return get_internal_str<TargetEnc>().template to_str<TargetEnc>();
	}


	template<typename... Encs>
	template<typename TargetEnc> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>::operator uni_string<TargetEnc>() const {
		return to_uni_str<TargetEnc>();
	}

	template<typename... Encs>
	template<class TargetEnc> OCT_CPP20_CONSTEXPR
	uni_string<TargetEnc> multi_uni_string<Encs...>::to_uni_str() const {
		return get_internal_str<TargetEnc>().template to_uni_str<TargetEnc>();
	}
}


namespace oct {
	template<typename... Encs> OCT_CPP20_CONSTEXPR 
	bool multi_uni_string<Encs...>::empty() const noexcept {
		bool empty = false;
		apply_to_each_str<impl::multi_str_empty>(empty);
		return empty;
	}
}



namespace oct {
	template<typename... Encs> OCT_CPP20_CONSTEXPR
	template<typename TargetEnc>
	byte_vector multi_uni_string<Encs...>::bytes() const {
		return to_uni_str<TargetEnc>().bytes();
	}
}



namespace oct{
	template<typename... Encs>
	template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::prepend(const uni_string<OtherEncoding>& uni_str) {
		apply_to_each_str<impl::multi_str_prepend>(uni_str);
		return *this;
	}
	
	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::prepend(str_arg<CharTy> str){
		return prepend(str, 0, npos);
	}
	
	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::prepend(const CharTy* const& str, size_t count){
		apply_to_each_str<impl::multi_str_prepend>(str, count);
		//apply_each(std::bind(impl::multi_str_prepend{}, std::placeholders::_1, str, count), strings);
		return *this;
	}
	
	template<typename... Encs>
	template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::prepend(const CharTy(&str_arr)[StrSize]){
		return prepend(&str_arr[0], impl::trimmed_size(str_arr));
	}
	
	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::prepend(CharTy c){
		return prepend(1, c);
	}


	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::prepend(size_t count, CharTy c){
		apply_to_each_str<impl::multi_str_prepend>(count, c);
		return *this;
	}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::prepend(str_arg<CharTy> str, size_t pos, size_t count){
		apply_to_each_str<impl::multi_str_prepend>(str, pos, count);
		return *this;
	}

	template<typename... Encs>
	template<typename InputIt, enable_if_input_iter<InputIt>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::prepend(InputIt srcBegin, InputIt srcEnd){
		apply_to_each_str<impl::multi_str_prepend>(srcBegin, srcEnd);
		return *this;
	}

	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::prepend(std::initializer_list<CharTy> char_list){
		apply_to_each_str<impl::multi_str_prepend>(char_list);
		return *this;
	}
}



namespace oct {
	template<typename... Encs>
	template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::append(const uni_string<OtherEncoding>& uni_str) {
		apply_to_each_str<impl::multi_str_append>(uni_str);
		return *this;
	}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::append(str_arg<CharTy> str) {
		return append(str, 0, npos);
	}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::append(const CharTy* const& str, size_t count) {
		apply_to_each_str<impl::multi_str_append>(str, count);
		return *this;
	}

	template<typename... Encs>
	template<typename CharTy, size_t StrSize> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::append(const CharTy(&str_arr)[StrSize]) {
		return append(&str_arr[0], impl::trimmed_size(str_arr));
	}

	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::append(CharTy c) {
		return append(1, c);
	}


	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::append(size_t count, CharTy c) {
		apply_to_each_str<impl::multi_str_append>(count, c);
		return *this;
	}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::append(str_arg<CharTy> str, size_t pos, size_t count) {
		apply_to_each_str<impl::multi_str_append>(str, pos, count);
		return *this;
	}

	template<typename... Encs>
	template<typename InputIt, enable_if_input_iter<InputIt>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::append(InputIt srcBegin, InputIt srcEnd) {
		apply_to_each_str<impl::multi_str_append>(srcBegin, srcEnd);
		return *this;
	}

	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::append(std::initializer_list<CharTy> char_list) {
		apply_to_each_str<impl::multi_str_append>(char_list);
		return *this;
	}
}


namespace oct {
	template<typename... Encs>
	template<typename OtherEncoding> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::operator+=(const uni_string<OtherEncoding>& uni_str) {
		return append(uni_str);
	}

	template<typename... Encs>
	template<typename CharTy, enable_if_integral<CharTy>> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::operator+=(CharTy c) {
		return append(c);
	}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::operator+=(str_arg<CharTy> str) {
		return append(str);
	}

	template<typename... Encs>
	template<typename CharTy> OCT_CPP20_CONSTEXPR
	multi_uni_string<Encs...>& multi_uni_string<Encs...>::operator+=(const CharTy* const& str) {
		return append(str);
	}
}



namespace oct {
	template<class CharTy, class Traits, typename... Encs>
	std::basic_ostream<CharTy, Traits>& operator<<(std::basic_ostream<CharTy, Traits>& os, const multi_uni_string<Encs...>& multi_str) {
		return os << multi_str.template to_str<Encoding<CharTy>>();
	}

	template<class CharTy, class Traits, typename... Encs>
	std::basic_istream<CharTy, Traits>& operator>>(std::basic_istream<CharTy, Traits>& is, multi_uni_string<Encs...>& multi_str) {
		apply([&is] (uni_string<Encs>&... tuple_args){
			(void)std::initializer_list<int> {
				((void)(is >> tuple_args), 0)...
			};
		}, multi_str.strings);
		return is;
	}
}



namespace oct {
	template<typename... Encs>
	template<typename Functor, typename... Args>
	void multi_uni_string<Encs...>::apply_to_each_str(Args&&... args) const {
		return apply_each(std::bind(Functor{}, std::placeholders::_1, std::forward<Args>(args)...), strings);
	}

	template<typename... Encs>
	template<typename Functor, typename... Args>
	void multi_uni_string<Encs...>::apply_to_each_str(Args&&... args) {
		return apply_each(std::bind(Functor{}, std::placeholders::_1, std::forward<Args>(args)...), strings);
	}
}



namespace oct {
	template<typename... Encs>
	template<typename Enc>
	struct multi_uni_string<Encs...>::contains :
		impl::tuple_index<
			typename multi_uni_string<Encs...>::internal_tuple_type, uni_string<Enc>, false
		>::valid {};

	#ifdef OCT_CPP17
	template<typename Enc, typename MultiStr>
	constexpr bool contains_v = multi_string_contains<MultiStr, Enc>::value;
	#endif



	template<typename... Encs>
	template<typename Enc> OCT_CPP14_CONSTEXPR 
	auto multi_uni_string<Encs...>::
	get_internal_str() const noexcept -> typename std::enable_if<contains<Enc>::value,
		decltype(oct::get<uni_string<Enc>>(strings)) >::type {
	
		return   oct::get<uni_string<Enc>>(strings);
	}

	template<typename... Encs>
	template<typename Enc> OCT_CPP14_CONSTEXPR 
	auto multi_uni_string<Encs...>::
	get_internal_str() const noexcept -> typename std::enable_if<!contains<Enc>::value,
		uni_string<Enc> >::type {

		static_assert(contains<Enc>::value, 
			"multi_uni_string does not contain given encoding!");

		return {};
	}
}



namespace oct {
	namespace impl {

		template<typename TupleStr>
		void multi_str_empty::operator()(TupleStr&& tuple_str, bool& empty) noexcept {
			empty = (std::forward<TupleStr>(tuple_str).empty() ? true : empty);
		}

		
		template<typename TupleStr, typename... ToPrepend>
		void multi_str_prepend::operator()(TupleStr&& tuple_str, ToPrepend&&... to_prepend) {
			std::forward<TupleStr>(tuple_str).prepend(std::forward<ToPrepend>(to_prepend)...);
		}

		template<typename TupleStr, typename... ToAppend>
		void multi_str_append::operator()(TupleStr&& tuple_str, ToAppend&&... to_append) {
			std::forward<TupleStr>(tuple_str).append(std::forward<ToAppend>(to_append)...);
		}
	}
}



template<typename... Encs>
std::size_t std::hash<oct::multi_uni_string<Encs...>>::operator()(const oct::multi_uni_string<Encs...>& s) const noexcept {
	std::size_t ret = 0, i = 0;
	(void)std::initializer_list<int> {
		((void)(ret ^= (std::hash<oct::uni_string<Encs>>{}(s.to_uni_str<Encs>()) << i++)), 0)...
	};
	return std::size_t();
}


#undef ASSERT_VALID_ENC