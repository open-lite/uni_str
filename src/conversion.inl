#include "../include/conversion.hpp"
#include <type_traits>


namespace oct {
    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_same_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str) {
        return std::basic_string<ToEnc::storage_type>(src_str); //NEEDS TO BE FIXED
    }

    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_same_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size) {
        return std::basic_string<typename ToEnc::storage_type>(src_str, src_size);
    }
}


namespace oct {
    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_same_size_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str) {
        return std::basic_string<typename ToEnc::storage_type>(src_str.begin(), src_str.cend());
    }

    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_same_size_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size) {
        return std::basic_string<typename ToEnc::storage_type>(
            reinterpret_cast<const typename ToEnc::storage_type*>(src_str), src_size
        );
    }
}


namespace oct {
    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_from_utf8_sized_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str) {
        return convert<FromEnc, ToEnc>(src_str.c_str(), src_str.size());
    }

    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_from_utf8_sized_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size) {
        std::basic_string<typename ToEnc::storage_type> ret;
        ret.reserve(impl::capacity_for<FromEnc>(src_str, src_size));

        size_t i = 0;
        unicode_cp_t ch;

        while (src_size != nsize ? i < src_size : src_str[i]) {
            ch = static_cast<uint8_t>(src_str[i++]);
            uint8_t trail_1, trail_2, trail_3;

            //Single byte character (0 <= ch <= 0x7F)
            if ((ch & 0x80) == 0)
                ret += static_cast<typename ToEnc::storage_type>(ch);

            /*Three byte character (0xE0 <= ch < 0xF0)
            * if ch is 0xE0: 0xA0 <= trail_1 <= 0xBF
            * if ch is 0xED: 0x80 <= trail_1 <= 0x9F
            * else:          0x80 <= trail_1 <= 0xBF
            * other trail:   0x80 <= trail_2 <= 0xBF
            */
            else if (((ch & 0xF0) == 0xE0) && (i + 1) < src_size &&
                ((trail_1 = src_str[i++]) || src_size != nsize) &&
                (trail_1 & 0xC0) == 0x80 &&
                (ch != 0xE0 || (trail_1 & 0xE0) == 0xA0) &&
                (ch != 0xED || (trail_1 & 0xE0) == 0x80) &&
                ((trail_2 = src_str[i++]) || src_size != nsize) &&
                (trail_2 & 0xC0) == 0x80)
                
                ret += ((ch & 0xF) << 12) | ((trail_1 & 0x3f) << 6) | (trail_2 & 0x3F);

            /*Two byte character (0xC2 <= ch < 0xE0)
            * 0x80 <= trail_1 <= 0xBF
            */
            else if (0xC2 <= ch && ch <= 0xDF && i < src_size && 
                ((trail_1 = src_str[i++]) || src_size != nsize) &&
                (trail_1 & 0xC0) == 0x80)

                ret += ((ch & 0x1F) << 6) | (trail_1 & 0x3F);

            /*Four byte character (0xC2 <= ch < 0xE0)
            * if ch is 0xF0: 0x90 <= trail_1 <= 0xBF
            * if ch is 0xF4: 0x80 <= trail_1 <= 0x8F
            * else:          0x80 <= trail_1 <= 0xBF
            * other trails:  0x80 <= trail_X <= 0xBF
            */
            else if (0xF0 <= ch && ch <= 0xF4 && (i + 2) < src_size &&
                ((trail_1 = src_str[i++]) || src_size != nsize) &&
                (trail_1 & 0xC0) == 0x80 &&
                (ch != 0xF0 || trail_1 >= 0x90) &&
                (ch != 0xF4 || trail_1 <= 0x8F) &&
                ((trail_2 = src_str[i++]) || src_size != nsize) &&
                (trail_2 & 0xC0) == 0x80 &&
                ((trail_3 = src_str[i++]) || src_size != nsize) &&
                (trail_3 & 0xC0) == 0x80)
            {
                unicode_cp_t cp = ((ch & 0x07) << 18) | ((trail_1 & 0x3F) << 12) | ((trail_2 & 0x3F) << 6) | (trail_3 & 0x3F);
                impl::surrogate_arr_t<ToEnc> surr = impl::utf<ToEnc>::surrogates(cp);
                ret.append(surr.data(), surr.size());
            }

            // Use UTF-16 replacement character for invalid code points
            else
                ret += static_cast<typename ToEnc::storage_type>(impl::replacement_char);
        }
        return ret;
    }
}
    

namespace oct {
    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_to_utf8_sized_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str) {
        return convert<FromEnc, ToEnc>(src_str.c_str(), src_str.size());
    }

    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_to_utf8_sized_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size) {
        //using ToStorageTy = typename ToEnc::storage_type;
        std::basic_string<typename ToEnc::storage_type> ret = std::basic_string<typename ToEnc::storage_type>();
        ret.reserve(impl::capacity_for<FromEnc>(src_str, src_size));

        size_t i = 0;
        uint32_t ch, trail = 0;

        while (src_size != nsize ? i < src_size : src_str[i]) {
            ch = src_str[i++];

            //U+0000 to U+007F
            if (ch <= 0x7F)
                ret += static_cast<typename ToEnc::storage_type>(ch);

            // U+007F to U+07FF
            else if (ch <= 0x7FF) {
                ret += static_cast<typename ToEnc::storage_type>((ch >> 6) | 0xC0);
                ret += static_cast<typename ToEnc::storage_type>((ch & 0x3F) | 0x80);
            }

            // U+0800 to U+D7FF and U+E000 to U+FFFF
            else if (ch <= 0xD7FF || (0xE000 <= ch && ch <= 0xFFFF)) {
            three_byte:
                ret += static_cast<typename ToEnc::storage_type>((ch >> 12) | 0xE0);
                ret += static_cast<typename ToEnc::storage_type>(((ch >> 6) & 0x3F) | 0x80);
                ret += static_cast<typename ToEnc::storage_type>((ch & 0x3F) | 0x80);
            }

            /* U+010000 to U+10FFFF
            *  trail surrogate is 0xDC00 to 0xDFFF
            *  lead surrogate (ch) is 0xD800 to 0xDBFF
            */
            else if (impl::utf<FromEnc>::is_supplementary_plane(ch, trail, src_str, i, src_size)) {
                ch = impl::utf<FromEnc>::supplementary_code_point(ch, trail);

                ret += static_cast<typename ToEnc::storage_type>((ch >> 18) | 0xF0);
                ret += static_cast<typename ToEnc::storage_type>(((ch >> 12) & 0x3F) | 0x80);
                ret += static_cast<typename ToEnc::storage_type>(((ch >> 6) & 0x3F) | 0x80);
                ret += static_cast<typename ToEnc::storage_type>((ch & 0x3F) | 0x80);
            }

            else {
                ch = impl::replacement_char;
                goto three_byte;
            }
        }

        return ret;
    }
}


namespace oct {
    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_utf_16_to_32_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str) {
        return convert<FromEnc, ToEnc>(src_str.c_str(), src_str.size());
    }

    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_utf_16_to_32_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size) {
        std::basic_string<typename ToEnc::storage_type> ret;
        ret.reserve(impl::capacity_for<FromEnc>(src_str, src_size));

        size_t i = 0;
        oct::unicode_cp_t ch;
        uint32_t trail = 0;

        while (src_size != nsize ? i < src_size : src_str[i]) {
            ch = src_str[i++];
            /* U+010000 to U+10FFFF
            *  trail surrogate is 0xDC00 to 0xDFFF
            *  lead (ch) is a lead surrogate
            */
            if (impl::utf<UTF16<typename FromEnc::storage_type>>::is_supplementary_plane(ch, trail, src_str, i, src_size))
                ch = impl::utf<UTF16<typename FromEnc::storage_type>>::supplementary_code_point(ch, trail);

            // ch is a surrogate (0xD800 <= ch <= 0xDFFF)
            // Use replacement character since its invalid
            else if (0xD800 <= ch && ch <= 0xDFFF)
                ch = impl::replacement_char;

            ret += ch;
        }

        return ret;
    }
}


namespace oct{
    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_utf_32_to_16_t<FromEnc, ToEnc> convert(str_arg<typename FromEnc::storage_type> src_str) {
        return convert<FromEnc, ToEnc>(src_str.c_str(), src_str.size());
    }

    template<typename FromEnc, typename ToEnc> OCT_CPP20_CONSTEXPR
    impl::enable_if_utf_32_to_16_t<FromEnc, ToEnc> convert(const typename FromEnc::storage_type* src_str, size_t src_size) {
        std::basic_string<typename ToEnc::storage_type> ret;
        ret.reserve(impl::capacity_for<FromEnc>(src_str, src_size));

        size_t i = 0;
        typename UTF32<typename FromEnc::storage_type>::char_type ch;

        while (src_size != nsize ? i < src_size : src_str[i]) {
            ch = src_str[i++];

            if (static_cast<uint32_t>(ch) <= 0xD7FF || (0xE000 <= ch && ch <= 0xFFFF))
                ret += static_cast<typename ToEnc::storage_type>(ch);

            else if (impl::utf<UTF32<typename FromEnc::storage_type>>::is_supplementary_plane(ch)) {
                ret += impl::lead_surrogate(ch);
                ret += impl::trail_surrogate(ch);
            }

            else
                ret += static_cast<typename ToEnc::storage_type>(impl::replacement_char);
        }

        return ret;
    }
}



//Helper function definitions
namespace oct {
    namespace impl {
        constexpr oct::UTF16<>::char_type lead_surrogate(oct::unicode_cp_t code_point) noexcept {
            return static_cast<oct::UTF16<>::char_type>(utf16_trail_surrogate_offset + (code_point >> 10));
        }

        constexpr oct::UTF16<>::char_type trail_surrogate(oct::unicode_cp_t code_point) noexcept {
            return static_cast<oct::UTF16<>::char_type>(0xDC00 + (code_point & 0x3FF));
        }
    }
}


namespace oct{
    namespace impl {
        //If the source is UTF16, get the supplementary code point. Otherwise, return the same code point.
        template<typename Enc>
        template<typename... UTF16Args>
        constexpr oct::unicode_cp_t oct::impl::utf<Enc>::supplementary_code_point(oct::unicode_cp_t code_point, UTF16Args...) {
            return code_point;
        }

        template<typename StorageTy>
        constexpr oct::unicode_cp_t oct::impl::utf<oct::UTF16<StorageTy>>::supplementary_code_point(oct::unicode_cp_t code_point, uint32_t trail) {
            return (code_point << 10) + trail - utf16_surrogate_offset;
        }


        // If the destination string is UTF16, return trail and lead surrogate. Otherwise, return just the code point.
        template<typename Enc> constexpr
        surrogate_arr_t<Enc> oct::impl::utf<Enc>::surrogates(oct::unicode_cp_t code_point) {
            return { static_cast<typename Enc::storage_type>(code_point) };
        }

        template<typename StorageTy> constexpr
        surrogate_arr_t<oct::UTF16<StorageTy>> oct::impl::utf<oct::UTF16<StorageTy>>::surrogates(oct::unicode_cp_t code_point) {
            return { lead_surrogate(code_point), trail_surrogate(code_point) };
        }


        //If the source is UTF16, check the surrogates as well. Otherwise, just check the code point.
        template<typename Enc>
        template<typename... UTF16Args>
        constexpr bool oct::impl::utf<Enc>::is_supplementary_plane(oct::unicode_cp_t cp, UTF16Args...) {
            return 0x10000 <= cp && cp <= 0x10FFFF;
        }
        
        template<typename StorageTy>
        constexpr bool oct::impl::utf<oct::UTF16<StorageTy>>::is_supplementary_plane(oct::unicode_cp_t cp, uint32_t& trail, const StorageTy* src_str, size_t& i, size_t src_size) {
            return (cp & 0x400) == 0 && i < src_size && ((trail = src_str[i++]) || src_size != nsize) && 0xDC00 <= trail && trail <= 0xDFFF;
        }
    }
}



namespace oct {
    namespace impl {

        template<typename CharTy> UNI_STR_STRLEN_CONSTEXPR
        size_t str_len(const CharTy* str) {
        #ifdef UNI_STR_USE_STD_STRLEN
            return std::char_traits<CharTy>::length(str);

        #else
            OCT_PUSH_WARN_PRE_CPP14

            if (!str) return nsize;
            const CharTy* end = str;
            for (; *end; ++end);
            return (end - str);

            OCT_POP_WARN
        #endif
        }
        

        template <typename Enc>
        constexpr size_t capacity_for(const typename Enc::storage_type* str, size_t size) {
            return (std::max)(impl::unicode_short_stackbuf_size, size == nsize ? str_len(str) : size + 1);
        }
    }
}
