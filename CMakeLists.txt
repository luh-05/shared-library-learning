cmake_minimum_required(VERSION 4.1)
project(sharedliblearning VERSION 1.0)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/bin/debug/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin/release/lib)

add_library(plugin_api INTERFACE)
target_include_directories(plugin_api
  INTERFACE
    ./plugin_api
)

add_library(plugin SHARED plugin/root.cpp)
target_link_libraries(plugin
  PRIVATE
    plugin_api
)

add_executable(host host/main.cpp)
target_link_libraries(host
  PRIVATE
    plugin_api
)
