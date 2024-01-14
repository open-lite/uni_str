#pragma once
#ifndef OCT_APPLY
#define OCT_APPLY

#include <tuple>
#include <cstdint>

#include "cpp_defs.h"
#include "integer_sequence.hpp"

#if defined(__cpp_lib_apply) && __cpp_lib_apply >= 201603L
#define OCT_HAS_STD_APPLY true
#endif


#ifndef OCT_HAS_STD_APPLY
namespace oct {
	namespace impl {
		template<typename F, typename Tuple, std::size_t... I>
		OCT_CPP14_CONSTEXPR auto
		apply(F&& f, Tuple && t, index_sequence<I...>) ->
			decltype(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...));
	}


	template<typename Func, typename Tuple>
	OCT_CPP14_CONSTEXPR auto 
	apply(Func&& f, Tuple&& t) ->
		decltype(impl::apply(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{}));
}
#else
namespace oct{
	using std::apply;
}
#endif



namespace oct {
	namespace impl {
		template<typename F, typename Tuple, std::size_t... I>
		OCT_CPP14_CONSTEXPR auto
		apply_each(F&& f, Tuple&& t, index_sequence<I...>) ->
			void;
	}


	template<typename Func, typename Tuple>
	OCT_CPP14_CONSTEXPR auto
	apply_each(Func&& f, Tuple&& t) ->
		decltype(impl::apply_each(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{}));
}



namespace oct {
	template<typename Tuple, typename... PrependArgs>
	OCT_CPP14_CONSTEXPR auto 
	prepended_tuple(Tuple&& t, PrependArgs&&... prepended_args) ->
		decltype(std::tuple_cat(
			std::forward_as_tuple(std::forward<PrependArgs>(prepended_args)...), std::forward<Tuple>(t)));
}

#include "../../../src/apply.inl"

#endif