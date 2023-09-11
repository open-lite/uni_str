#pragma once
#ifndef OCT_TUPLE_INDEX
#define OCT_TUPLE_INDEX

#include <tuple>
#include <type_traits>
#include <utility>

#include "cpp_defs.h"


namespace oct {
	namespace impl {
		template<typename Tuple, typename T, bool VerifyCount = true, size_t = 0, size_t = 0 >
		struct tuple_index {
			static_assert(!std::is_same<Tuple, Tuple>::value, "First type passed to tuple_index must be a std::tuple!");
		};


		template <typename T, typename Head, typename... Tail, bool VerifyCount, size_t I, size_t count>
		struct tuple_index<std::tuple<Head, Tail...>, T, VerifyCount, I, count>
			:  tuple_index<std::tuple<Tail...>, T, VerifyCount, I + 1, count> {};


		template<typename MatchingT, typename... Rest, bool VerifyCount, size_t I, size_t count>
		struct tuple_index<std::tuple<MatchingT, Rest...>, MatchingT, VerifyCount, I, count>
			:  tuple_index<std::tuple<Rest...>, MatchingT, VerifyCount, I + 1, count + 1> {

			constexpr static size_t value = I;
		};


		template<typename T, bool VerifyCount, size_t I, size_t count>
		struct tuple_index<std::tuple<>, T, VerifyCount, I, count> {

			struct valid : std::integral_constant<bool, (count == 1)> {};

			static_assert(count != 0 || !VerifyCount, "Tuple does not contain given type!");
			static_assert(count <= 1 || !VerifyCount, "More than one occurance of the same type in tuple!");
		};
	}
}

#endif