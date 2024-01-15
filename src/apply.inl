#include "uni_str/common/apply.hpp"


#ifndef OL_HAS_STD_APPLY
namespace ol {
	namespace impl {
		template<typename F, typename Tuple, std::size_t... I>
		OL_CPP14_CONSTEXPR auto
		apply(F&& f, Tuple && t, index_sequence<I...>) ->
			decltype(std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...)) {

			return   std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
		}
	}
}
#endif


namespace ol {
	namespace impl {
		template<typename F, typename Tuple, std::size_t... I>
		OL_CPP14_CONSTEXPR auto
		apply_each(F&& f, Tuple&& t, index_sequence<I...>) -> void {
			OL_PUSH_WARN_PRE_CPP14

			(void)std::initializer_list<int> {
				((void)std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))), 0)...
			};
			return;

			OL_POP_WARN
		}
	}
}



#ifndef OL_HAS_STD_APPLY
namespace ol {
	template<typename Func, typename Tuple>
	OL_CPP14_CONSTEXPR auto 
	apply(Func&& f, Tuple&& t) ->
		decltype(impl::apply(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{})){

		return   impl::apply(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{});
	}
}
#endif


namespace ol {
	template<typename Func, typename Tuple>
	OL_CPP14_CONSTEXPR auto
	apply_each(Func&& f, Tuple&& t) ->
		decltype(impl::apply_each(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{})) {

		return   impl::apply_each(std::forward<Func>(f), std::forward<Tuple>(t),
			make_index_sequence<std::tuple_size<typename std::decay<Tuple>::type>::value>{});
	}
}



namespace ol {
	template<typename Tuple, typename... PrependArgs>
	OL_CPP14_CONSTEXPR auto
	prepended_tuple(Tuple&& t, PrependArgs&&... prepended_args) ->
		decltype(std::tuple_cat(
			std::forward_as_tuple(std::forward<PrependArgs>(prepended_args)...), std::forward<Tuple>(t))) {

		return   std::tuple_cat(
			std::forward_as_tuple(std::forward<PrependArgs>(prepended_args)...), std::forward<Tuple>(t));
	}
}