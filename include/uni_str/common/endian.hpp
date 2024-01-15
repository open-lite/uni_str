#pragma once

#include <cstdint>

#include "file_versioning.hpp"



// This file is versioned because more endian variables (other than just "little" and "big") may need to be added
#define OL_ENDIAN_MAJOR_US 1
#define OL_ENDIAN_MINOR_US 0


#if  OL_ENDIAN_MAJOR  < OL_ENDIAN_MAJOR_US || \
	(OL_ENDIAN_MAJOR == OL_ENDIAN_MAJOR_US && OL_ENDIAN_MINOR <= OL_ENDIAN_MINOR_US)
#define OL_ENDIAN_US_IS_NEWER true
#endif



#if  !defined(OL_ENDIAN_MAJOR) || \
    (!defined(OL_ENDIAN_DECLARED) && defined(OL_ENDIAN_US_IS_NEWER))


namespace ol {
	namespace endian {
		namespace impl {
			constexpr uint32_t uint32_constant = 0x01020304;
			constexpr uint8_t  test_byte = (const uint8_t&)uint32_constant;
		}

		constexpr bool little = impl::test_byte == 0x4;
		constexpr bool big = impl::test_byte == 0x1;
	}
}



#undef OL_ENDIAN 
#undef OL_ENDIAN_MAJOR
#undef OL_ENDIAN_MINOR

#define OL_ENDIAN          OL_VERSION_STR(OL_ENDIAN_MAJOR_US, OL_ENDIAN_MINOR_US)
#define OL_ENDIAN_MAJOR    OL_ENDIAN_MAJOR_US
#define OL_ENDIAN_MINOR    OL_ENDIAN_MINOR_US
#define OL_ENDIAN_DECLARED true

#elif defined(OL_ENDIAN_US_IS_NEWER)
#pragma message(OL_OUTDATED_WARN(endian, OL_ENDIAN_MAJOR, OL_ENDIAN_MINOR, OL_ENDIAN_MAJOR_US, OL_ENDIAN_MINOR_US))
#endif
