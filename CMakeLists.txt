project(attica)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_LIBATTICA_VERSION_MAJOR 0)
set(CMAKE_LIBATTICA_VERSION_MINOR 4)
set(CMAKE_LIBATTICA_VERSION_PATCH 1)
set(CMAKE_LIBATTICA_VERSION_STRING  "${CMAKE_LIBATTICA_VERSION_MAJOR}.${CMAKE_LIBATTICA_VERSION_MINOR}.${CMAKE_LIBATTICA_VERSION_PATCH}")

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -Wall -Wno-switch -O2 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Wall -Wno-switch -O2")
    set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -Wall -Wno-switch -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE)
endif(NOT MSVC)

add_definitions( -DQT_NO_CAST_FROM_ASCII )
add_definitions( -DQT_NO_CAST_TO_ASCII )
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

# Enable static build
option(ATTICA_STATIC_BUILD "Build a static library" Off)

# Enable unit testing
option(ATTICA_ENABLE_TESTS "Enable tests" ON)
if (ATTICA_ENABLE_TESTS)
    enable_testing()
endif (ATTICA_ENABLE_TESTS)

set(CMAKE_INSTALL_NAME_DIR ${LIB_INSTALL_DIR})

add_subdirectory(lib)

