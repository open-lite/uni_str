cmake_minimum_required(VERSION 3.12)
project(uni_str VERSION 1.0.0 HOMEPAGE_URL https://github.com/open-lite/uni_str)

list(APPEND HEADERS
    "include/uni_str/common/apply.hpp"
    "include/uni_str/common/cpp_defs.h"
    "include/uni_str/common/endian.hpp"
    "include/uni_str/common/file_versioning.hpp"
    "include/uni_str/common/get.hpp"
    "include/uni_str/common/integer_sequence.hpp"
    "include/uni_str/common/split_into_bytes.hpp"
    "include/uni_str/common/tuple_index.hpp"
    "include/uni_str/common/type_defs.hpp"
_
    "src/apply.inl"
    

    "include/uni_str/conversion.hpp"
    "src/conversion.inl"

    "include/uni_str/encoding.hpp"

    "include/uni_str/multi_string.hpp"
    "src/multi_string.inl"

    "include/uni_str/uni_string.hpp"
    "src/uni_string.inl"
)


#set(CMAKE_CXX_CLANG_TIDY clang-tidy;-checks=-*,cppcoreguidelines-*,modernize-*,performance-*,portability-*,readability-*;-header-filter=.*)

add_library(${PROJECT_NAME} INTERFACE)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${HEADERS}"
)

target_include_directories(${PROJECT_NAME} INTERFACE ./include)