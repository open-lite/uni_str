#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

#include "cpp_defs.h"

#ifndef OCT_TUPLE_INDEX
#define OCT_TUPLE_INDEX


#if !defined(__cpp_lib_apply) || __cpp_lib_apply < 201603L
#define UNI_STR_APPLY_IMPL \
impl::tuple_index<typename std::decay<Tuple>::type, void, impl::apply_fn_mode::Apply, false>::                             \
	apply(std::forward<Func>(f), std::forward<Tuple>(t), std::forward<PrependArgs>(prepended_args)...)

#else
#define UNI_STR_APPLY_IMPL \
std::apply(std::forward<Func>(f), std::tuple_cat(                                                \
	std::forward_as_tuple(std::forward<PrependArgs>(prepended_args)...), std::forward<Tuple>(t)  \
))

#endif



namespace oct {
	namespace impl {
		enum class apply_fn_mode {
			None, Apply, ApplyEach
		};


		template<
			typename Tuple, typename T, 
			apply_fn_mode ApplyMode = apply_fn_mode::None, 
			bool VerifyCount = true,
		size_t = 0, size_t = 0>
		struct tuple_index;

		template<apply_fn_mode ApplyMode>
		struct apply_impl;
	} 
}



namespace oct {
	template<typename Func, typename Tuple, typename... PrependArgs> 
	OCT_CPP14_CONSTEXPR auto 
	apply(Func&& f, Tuple&& t, PrependArgs&&... prepended_args) ->
		decltype(UNI_STR_APPLY_IMPL);


	template<typename Func, typename Tuple> 
	OCT_CPP14_CONSTEXPR auto 
	apply_each(Func&& f, Tuple&& t) ->
		void;
}


namespace oct {
	#if !defined(__cpp_lib_tuples_by_type) || __cpp_lib_tuples_by_type < 201304L

	template<class T, class Tuple, enable_if_tuple<Tuple> = true>
	auto get(Tuple&& t) noexcept ->
		decltype(std::get<impl::tuple_index<Tuple, T>::value>(std::forward<Tuple>(t)));

	#endif
	

	using std::get;
}



namespace oct {
	namespace impl {
		template<typename Tuple, typename T, apply_fn_mode ApplyMode, bool VerifyCount, size_t , size_t >
		struct tuple_index {
			static_assert(!std::is_same<Tuple, Tuple>::value, "First type passed to tuple_index must be a std::tuple!");
		};


		template <typename T, typename Head, typename... Tail, apply_fn_mode ApplyMode, bool VerifyCount, size_t I, size_t count>
		struct tuple_index<std::tuple<Head, Tail...>, T, ApplyMode, VerifyCount, I, count> : tuple_index<std::tuple<Tail...>, T, ApplyMode, VerifyCount, I + 1, count> {

			template<typename Func, typename Tuple, typename... TupleElems>
			OCT_CPP14_CONSTEXPR static auto
			apply(Func&& f, Tuple&& t, TupleElems&&... tuple_elems) ->
				decltype(tuple_index<std::tuple<Tail...>, T, ApplyMode, VerifyCount, I + 1, count>::
					apply(std::forward<Func>(f), std::forward<Tuple>(t), std::forward<TupleElems>(tuple_elems)..., std::get<I>(t)));
		};


		template<typename MatchingT, typename... Rest, apply_fn_mode ApplyMode, bool VerifyCount, size_t I, size_t count>
		struct tuple_index<std::tuple<MatchingT, Rest...>, MatchingT, ApplyMode, VerifyCount, I, count> : tuple_index<std::tuple<Rest...>, MatchingT, ApplyMode, VerifyCount, I + 1, count + 1> {

			constexpr static size_t value = I;

			template<typename Func, typename Tuple, typename... TupleElems> 
			OCT_CPP14_CONSTEXPR static auto 
			apply(Func&& f, Tuple&& t, TupleElems&&... tuple_elems) ->
				decltype(tuple_index<std::tuple<Rest...>, MatchingT, ApplyMode, VerifyCount, I + 1, count + 1>::
					apply(std::forward<Func>(f), std::forward<Tuple>(t), std::forward<TupleElems>(tuple_elems)..., std::get<I>(t)));
		};


		template<typename T, apply_fn_mode ApplyMode, bool VerifyCount, size_t I, size_t count>
		struct tuple_index<std::tuple<>, T, ApplyMode, VerifyCount, I, count> : apply_impl<ApplyMode>{

			struct valid_type : std::integral_constant<bool, (count == 1)> {};

			static_assert(count != 0 || !VerifyCount, "Tuple does not contain given type!");
			static_assert(count <= 1 || !VerifyCount, "More than one occurance of the same type in tuple!");
		};


		template<>
		struct apply_impl<apply_fn_mode::ApplyEach> {
			template<typename Func, typename Tuple, typename... TupleElems>
			OCT_CPP14_CONSTEXPR static auto
			apply(Func&& f, Tuple&& t, TupleElems&&... tuple_elems) ->
				void;
		};

		template<>
		struct apply_impl<apply_fn_mode::Apply> {
			template<typename Func, typename Tuple, typename... TupleElems>
			OCT_CPP14_CONSTEXPR static auto
			apply(Func&& f, Tuple&& t, TupleElems&&... tuple_elems) ->
				decltype(std::forward<Func>(f)(std::forward<TupleElems>(tuple_elems)...));
		};

		template<>
		struct apply_impl<apply_fn_mode::None> {
			template<typename Func, typename Tuple, typename... TupleElems>
			OCT_CPP14_CONSTEXPR static auto
			apply(Func&&, Tuple&&, TupleElems&&...) -> void {
				static_assert(!std::is_same<Func, Func>::value,
					"Cannot call tuple_index<...>::apply() when ApplyMode = apply_fn_mode::None!");
				return;
			}
		};
	}
}



#include "../../src/tuple_index.inl"

#undef UNI_STR_APPLY_IMPL

#endif