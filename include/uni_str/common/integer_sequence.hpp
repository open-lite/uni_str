#pragma once
#ifndef OCT_INT_SEQ
#define OCT_INT_SEQ

#include <cstdint>

#if defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304L
#define OCT_HAS_STD_INT_SEQ true
#endif


// Prefer std's implementation of integer_sequence 
// for compatibility with functions that specifically expect it from std::
#if defined(OCT_HAS_STD_INT_SEQ)

#include <utility>

namespace oct {
    using std::integer_sequence;

    using std::index_sequence;
}

#else

namespace oct {
    template <typename T, T... Is>
    struct integer_sequence {
        static_assert(std::is_integral<T>::value, "integer_sequence<T, I...> requires T to be an integral type.");

        using value_type = T;
        constexpr static T size() noexcept { return sizeof...(Is); }
    };


    template<size_t... Is>
    using index_sequence = integer_sequence<size_t, Is...>;
}

#endif 

//common O(log n) integer sequence implementation, but with reversing added
namespace oct { 
    namespace impl {
        template <typename T, class Lhs, class Rhs, bool Reversed>
        struct merge_int_seqs;


        template <typename T, T... LIs, T... RIs>
        struct impl::merge_int_seqs<T, integer_sequence<T, LIs...>, integer_sequence<T, RIs...>, false> {
            using seq_type = integer_sequence<T, LIs..., sizeof...(LIs) + RIs...>;
        };

        template <typename T, T... LIs, T... RIs>
        struct impl::merge_int_seqs<T, integer_sequence<T, LIs...>, integer_sequence<T, RIs...>, true> {
            using seq_type = integer_sequence<T, sizeof...(LIs) + RIs..., LIs...>;
        };


        template <typename T, typename Constant, bool Reversed>
        struct make_integer_sequence;

        template <typename T, T N, bool Reversed>
        struct make_integer_sequence<T, std::integral_constant<T, N>, Reversed> : impl::merge_int_seqs<T,
            typename make_integer_sequence<T, std::integral_constant<T, N / 2    >, Reversed>::seq_type,
            typename make_integer_sequence<T, std::integral_constant<T, N - N / 2>, Reversed>::seq_type,
        Reversed> {}; 

        template<typename T, bool R> struct make_integer_sequence<T, std::integral_constant<T, 0>, R> { using seq_type = integer_sequence<T>; };
        template<typename T, bool R> struct make_integer_sequence<T, std::integral_constant<T, 1>, R> { using seq_type = integer_sequence<T, 0>; };
    }

    template <typename T, T N, bool Reversed = false>
    struct make_integer_sequence : impl::make_integer_sequence<T, std::integral_constant<T, N>, Reversed>::seq_type {
        static_assert(N >= 0, "Cannot make a negative length integer sequence!");
    };
}


#if defined(OCT_HAS_STD_INT_SEQ) 
//use std's make_integer_sequence when not reversed if it's available
namespace oct {
    template <typename T, T N>
    struct make_integer_sequence<T, N, false> : std::make_integer_sequence<T, N> {};
}
#endif


namespace oct {
    template<size_t N, bool Reversed = false>
    using make_index_sequence = make_integer_sequence<size_t, N, Reversed>;


    template<class... T>
    using index_sequence_for = make_index_sequence<sizeof...(T)>;
}

#endif