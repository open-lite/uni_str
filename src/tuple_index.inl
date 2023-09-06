#include "tuple_index.hpp"

#include <utility>
#include <initializer_list>



namespace oct {
	template<typename Func, typename Tuple, typename... PrependArgs>
	auto UNI_STR_CPP14_CONSTEXPR
	apply(Func&& f, Tuple&& t, PrependArgs&&... prepended_args) ->
		decltype(UNI_STR_APPLY_IMPL) {

		return   UNI_STR_APPLY_IMPL;
	}


	template<typename Func, typename Tuple>
	auto UNI_STR_CPP14_CONSTEXPR
	apply_each(Func&& f, Tuple&& t) -> void {
		return impl::tuple_index<typename std::decay<Tuple>::type, void, impl::apply_fn_mode::ApplyEach, false>::
			apply(std::forward<Func>(f), std::forward<Tuple>(t));
	}
}


namespace oct {
#if !defined(__cpp_lib_tuples_by_type) || __cpp_lib_tuples_by_type < 201304L
	template<class T, class Tuple, enable_if_tuple<Tuple> = true>
	auto get(Tuple&& t) noexcept ->
		decltype(std::get<impl::tuple_index<Tuple, T>::value>(std::forward<Tuple>(t))) {

		return   std::get<impl::tuple_index<Tuple, T>::value>(std::forward<Tuple>(t));
	}
#endif
}



namespace oct {
	namespace impl {
		template<typename T, typename Head, typename... Tail, apply_fn_mode ApplyMode, bool VerifyCount, size_t I, size_t count>
		template<typename Func, typename Tuple, typename... TupleElems>
		UNI_STR_CPP14_CONSTEXPR auto 
		tuple_index<std::tuple<Head, Tail...>, T, ApplyMode, VerifyCount, I, count>::
		apply(Func&& f, Tuple&& t, TupleElems&&... tuple_elems) ->
			decltype(tuple_index<std::tuple<Tail...>, T, ApplyMode, VerifyCount, I + 1, count>::
				apply(std::forward<Func>(f), std::forward<Tuple>(t), std::forward<TupleElems>(tuple_elems)..., std::get<I>(t))) {

			static_assert(I != 0 || std::tuple_size<typename std::decay<Tuple>::type>::value == std::tuple_size < std::tuple<Head, Tail...>>::value,
				"Tuple passed to oct::tuple_index<...>::apply does not match the size of the tuple passed to oct::tuple_index<...>!");

			return   tuple_index<std::tuple<Tail...>, T, ApplyMode, VerifyCount, I + 1, count>::
				apply(std::forward<Func>(f), std::forward<Tuple>(t), std::forward<TupleElems>(tuple_elems)..., std::get<I>(t));
		}


		template<typename MatchingT, typename... Rest, apply_fn_mode ApplyMode, bool VerifyCount, size_t I, size_t count>
		template<typename Func, typename Tuple, typename... TupleElems>
		UNI_STR_CPP14_CONSTEXPR auto 
		tuple_index<std::tuple<MatchingT, Rest...>, MatchingT, ApplyMode, VerifyCount, I, count>::
		apply(Func&& f, Tuple&& t, TupleElems&&... tuple_elems) ->
			decltype(tuple_index<std::tuple<Rest...>, MatchingT, ApplyMode, VerifyCount, I + 1, count + 1>::
				apply(std::forward<Func>(f), std::forward<Tuple>(t), std::forward<TupleElems>(tuple_elems)..., std::get<I>(t))) {

			static_assert(I != 0 || std::tuple_size<typename std::decay<Tuple>::type>::value == std::tuple_size<std::tuple<MatchingT, Rest...>>::value,
				"Tuple passed to oct::tuple_index<...>::apply does not match the size of the tuple passed to oct::tuple_index<...>!");
			
			return   tuple_index<std::tuple<Rest...>, MatchingT, ApplyMode, VerifyCount, I + 1, count + 1>::
				apply(std::forward<Func>(f), std::forward<Tuple>(t), std::forward<TupleElems>(tuple_elems)..., std::get<I>(t));
		}
	}
}



namespace oct {
	namespace impl {
		template<typename Func, typename Tuple, typename... TupleElems>
		UNI_STR_CPP14_CONSTEXPR auto
		apply_impl<apply_fn_mode::ApplyEach>::
		apply(Func&& f, Tuple&&, TupleElems&&... tuple_elems) -> void {
			UNI_STR_PUSH_WARN_PRE_CPP14

			using expander = std::initializer_list<int>;
			(void)expander {
				((void)std::forward<Func>(f)(std::forward<TupleElems>(tuple_elems)), 0)...
			};
			return;

			UNI_STR_POP_WARN
		}

		template<typename Func, typename Tuple, typename... TupleElems>
		UNI_STR_CPP14_CONSTEXPR auto
		apply_impl<apply_fn_mode::Apply>::
		apply(Func&& f, Tuple&&, TupleElems&&... tuple_elems) ->
			decltype(std::forward<Func>(f)(std::forward<TupleElems>(tuple_elems)...)) {

			return   std::forward<Func>(f)(std::forward<TupleElems>(tuple_elems)...);
		}
	}
}