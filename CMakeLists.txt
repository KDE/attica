project(attica)

set(ATTICA_VERSION_MAJOR 0 CACHE INT "Major Attica version number" FORCE)
set(ATTICA_VERSION_MINOR 1 CACHE INT "Minor Attica version number" FORCE)
set(ATTICA_VERSION_PATCH 0 CACHE INT "Release Attica version number" FORCE)
set(ATTICA_VERSION_STRING "${ATTICA_VERSION_MAJOR}.${ATTICA_VERSION_MINOR}.${ATTICA_VERSION_PATCH}" CACHE STRING "Attica version string" FORCE)

cmake_minimum_required(VERSION 2.6)

add_subdirectory(lib)

