project(attica)

set(CMAKE_LIBATTICA_VERSION_MAJOR 0 CACHE INT "Major Attica version number" FORCE)
set(CMAKE_LIBATTICA_VERSION_MINOR 2 CACHE INT "Minor Attica version number" FORCE)
set(CMAKE_LIBATTICA_VERSION_PATCH 1 CACHE INT "Release Attica version number" FORCE)
set(CMAKE_LIBATTICA_VERSION_STRING "${CMAKE_LIBATTICA_VERSION_MAJOR}.${CMAKE_LIBATTICA_VERSION_MINOR}.${CMAKE_LIBATTICA_VERSION_PATCH}" CACHE STRING "Attica version string" FORCE)

cmake_minimum_required(VERSION 2.6)
add_definitions( -DQT_NO_CAST_FROM_ASCII ) # FIXME: re-enable when OBS classes are fixed (sebas)
add_definitions( -DQT_NO_CAST_TO_ASCII )


# Enable unit testing
option(ATTICA_ENABLE_TESTS "Enable tests")
if (ATTICA_ENABLE_TESTS)
    enable_testing()
endif (ATTICA_ENABLE_TESTS)

set(CMAKE_INSTALL_NAME_DIR ${LIB_INSTALL_DIR})

add_subdirectory(lib)

