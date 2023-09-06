#pragma once
#include <cstdint>

#ifndef OCT_ENDIAN
#define OCT_ENDIAN
namespace oct {
	namespace endian {
		namespace impl {
			constexpr uint32_t reference_uint32 = 0x01020304;
			constexpr uint8_t  test_byte = (const uint8_t&)reference_uint32;
		}

		constexpr bool little = impl::test_byte == 0x4;
		constexpr bool big = impl::test_byte == 0x1;
	}
}
#endif