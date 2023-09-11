#include "../include/common/apply.hpp"


#ifndef OCT_HAS_STD_APPLY
namespace oct {
	namespace impl {
		template<typename F, typename Tuple, std::size_t... I>
		OCT_CPP14_CONSTEXPR auto
		apply(F&& f, Tuple && t, index_sequence<I...>) ->
			decltype(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...)) {

			return   std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
		}
	}
}
#endif


namespace oct {
	namespace impl {
		template<typename F, typename Tuple, std::size_t... I>
		OCT_CPP14_CONSTEXPR auto
		apply_each(F&& f, Tuple&& t, index_sequence<I...>) -> void {
			OCT_PUSH_WARN_PRE_CPP14

			(void)std::initializer_list<int> {
				((void)std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))), 0)...
			};
			return;

			OCT_POP_WARN
		}
	}
}



#ifndef OCT_HAS_STD_APPLY
namespace oct {
	template<typename Func, typename Tuple>
	OCT_CPP14_CONSTEXPR auto 
	apply(Func&& f, Tuple&& t) ->
		decltype(impl::apply(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{})){

		return   impl::apply(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{});
	}
}
#endif


namespace oct {
	template<typename Func, typename Tuple>
	OCT_CPP14_CONSTEXPR auto
	apply_each(Func&& f, Tuple&& t) ->
		decltype(impl::apply_each(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{})) {

		return   impl::apply_each(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{});
	}
}



namespace oct {
	template<typename Tuple, typename... PrependArgs>
	OCT_CPP14_CONSTEXPR auto
	prepended_tuple(Tuple&& t, PrependArgs&&... prepended_args) ->
		decltype(std::tuple_cat(
			std::forward_as_tuple(std::forward<PrependArgs>(prepended_args)...), std::forward<Tuple>(t))) {

		return   std::tuple_cat(
			std::forward_as_tuple(std::forward<PrependArgs>(prepended_args)...), std::forward<Tuple>(t));
	}
}