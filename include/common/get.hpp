#pragma once

#include <tuple>

#include "tuple_index.hpp"

namespace oct {
#if !defined(__cpp_lib_tuples_by_type) || __cpp_lib_tuples_by_type < 201304L

	template<class T, class Tuple, enable_if_tuple_like<Tuple> = true>
	auto get(Tuple&& t) noexcept ->
		decltype(std::get<impl::tuple_index<Tuple, T>::value>(std::forward<Tuple>(t))) {

		return   std::get<impl::tuple_index<Tuple, T>::value>(std::forward<Tuple>(t));
	}

#endif


	using std::get;
}