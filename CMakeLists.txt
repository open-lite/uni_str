cmake_minimum_required(VERSION 3.12)
project(UniversalString VERSION 1.0.0 HOMEPAGE_URL https://github.com/OpenCompileTools/UniversalString)
set(EXPORT_NAME "UNI_STR")


option(LINK_32_BIT "Link the UniversalString library for a 32-bit target" OFF)

list(APPEND HEADEERS
    "include/common.h"

    "include/encoding.h"

    "include/uni_string.hpp"
    "src/uni_string.inl"

    "include/multi_string.hpp"
    "src/multi_string.inl"

    "include/conversion.hpp"
    "src/conversion.inl"
)

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