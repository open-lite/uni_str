cmake_minimum_required(VERSION 3.12)
project(UniversalString VERSION 1.0.0 HOMEPAGE_URL https://github.com/OpenCompileTools/UniversalString)
set(EXPORT_NAME "UNI_STR")

option(LINK_32_BIT "Link the UniversalString library for a 32-bit target" OFF)

list(APPEND HEADERS
    "include/common/apply.hpp"
    "include/common/cpp_defs.h"
    "include/common/endian.hpp"
    "include/common/file_versioning.hpp"
    "include/common/get.hpp"
    "include/common/integer_sequence.hpp"
    "include/common/split_into_bytes.hpp"
    "include/common/tuple_index.hpp"
    "include/common/type_defs.hpp"

    "src/apply.inl"
    

    "include/conversion.hpp"
    "src/conversion.inl"

    "include/encoding.hpp"

    "include/multi_string.hpp"
    "src/multi_string.inl"

    "include/uni_string.hpp"
    "src/uni_string.inl"
)


#set(CMAKE_CXX_CLANG_TIDY clang-tidy;-checks=-*,cppcoreguidelines-*,modernize-*,performance-*,portability-*,readability-*;-header-filter=.*)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${EXPORT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${HEADERS}"
)

if(BUILD_32_BIT)
set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS "-m32"
    LINK_FLAGS "-m32"
)
endif()

target_include_directories(${PROJECT_NAME} INTERFACE ./include)