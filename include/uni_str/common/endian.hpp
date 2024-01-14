#pragma once

#include <cstdint>

#include "file_versioning.hpp"



// This file is versioned because more endian variables (other than just "little" and "big") may need to be added
#define OCT_ENDIAN_MAJOR_US 1
#define OCT_ENDIAN_MINOR_US 0


#if  OCT_ENDIAN_MAJOR  < OCT_ENDIAN_MAJOR_US || \
	(OCT_ENDIAN_MAJOR == OCT_ENDIAN_MAJOR_US && OCT_ENDIAN_MINOR <= OCT_ENDIAN_MINOR_US)
#define OCT_ENDIAN_US_IS_NEWER true
#endif



#if  !defined(OCT_ENDIAN_MAJOR) || \
    (!defined(OCT_ENDIAN_DECLARED) && defined(OCT_ENDIAN_US_IS_NEWER))


namespace oct {
	namespace endian {
		namespace impl {
			constexpr uint32_t uint32_constant = 0x01020304;
			constexpr uint8_t  test_byte = (const uint8_t&)uint32_constant;
		}

		constexpr bool little = impl::test_byte == 0x4;
		constexpr bool big = impl::test_byte == 0x1;
	}
}



#undef OCT_ENDIAN 
#undef OCT_ENDIAN_MAJOR
#undef OCT_ENDIAN_MINOR

#define OCT_ENDIAN          OCT_VERSION_STR(OCT_ENDIAN_MAJOR_US, OCT_ENDIAN_MINOR_US)
#define OCT_ENDIAN_MAJOR    OCT_ENDIAN_MAJOR_US
#define OCT_ENDIAN_MINOR    OCT_ENDIAN_MINOR_US
#define OCT_ENDIAN_DECLARED true

#elif defined(OCT_ENDIAN_US_IS_NEWER)
#pragma message(OCT_OUTDATED_WARN(endian, OCT_ENDIAN_MAJOR, OCT_ENDIAN_MINOR, OCT_ENDIAN_MAJOR_US, OCT_ENDIAN_MINOR_US))
#endif
