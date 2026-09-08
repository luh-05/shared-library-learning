cmake_minimum_required(VERSION 4.1)
project(sharedliblearning LANGUAGES C CXX VERSION 1.0)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/bin/debug/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release/lib)

# ABI
add_library(plugin_abi INTERFACE)
target_include_directories(plugin_abi
  INTERFACE
    ./plugin_abi
)

# C library that will fail to build when c++ features are present in the ABI
add_library(abi_header_check STATIC abi_check.c)
target_link_libraries(abi_header_check PRIVATE plugin_abi)

set_target_properties(abi_header_check PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(abi_header_check PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# targets
add_library(plugin SHARED plugin/root.cpp)
target_link_libraries(plugin
  PRIVATE
    plugin_abi
)

add_executable(host host/main.cpp)
target_link_libraries(host
  PRIVATE
    plugin_abi
)
target_include_directories(host
  PRIVATE
   ./host
)
