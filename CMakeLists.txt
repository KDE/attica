project(attica)
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

option(QT4_BUILD "Force building with Qt4 even if Qt5 is found")
if (NOT QT4_BUILD)
  find_package(Qt5Core QUIET)
endif()

# Used to create CMake config files
include(CMakePackageConfigHelpers)

# Used to set installation paths
include(GNUInstallDirs)

# Set the different paths
set(LIB_DESTINATION         "${CMAKE_INSTALL_FULL_LIBDIR}" CACHE PATH "Library directory name")
set(INCLUDE_DESTINATION     "${CMAKE_INSTALL_FULL_INCLUDEDIR}" CACHE PATH "The subdirectory to the header prefix")

if (Qt5Core_FOUND)
  message(STATUS "Building with Qt5 support")
  find_package(Qt5Transitional REQUIRED Core Network)
else()
  set(QT_MIN_VERSION "4.7.0")
  find_package(Qt4 REQUIRED)
endif()

if (Qt5Core_FOUND)
  set(CMAKE_LIBATTICA_VERSION_MAJOR 1)
  set(CMAKE_LIBATTICA_VERSION_MINOR 0)
  set(CMAKE_LIBATTICA_VERSION_PATCH 0)
else()
  set(CMAKE_LIBATTICA_VERSION_MAJOR 0)
  set(CMAKE_LIBATTICA_VERSION_MINOR 4)
  set(CMAKE_LIBATTICA_VERSION_PATCH 2)
endif()
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

add_subdirectory(lib)

# Write LibAtticaConfigVersion.cmake
write_basic_package_version_file(${attica_BINARY_DIR}/LibAtticaConfigVersion.cmake
                                 VERSION ${CMAKE_LIBATTICA_VERSION_STRING}
                                 COMPATIBILITY SameMajorVersion
                                )

# Create the CMake Config files
configure_package_config_file(LibAtticaConfig.cmake.in
                              ${attica_BINARY_DIR}/LibAtticaConfig.cmake
                              INSTALL_DESTINATION ${LIB_DESTINATION}/cmake/LibAttica
                              PATH_VARS LIB_DESTINATION INCLUDE_DESTINATION
)

install(FILES ${attica_BINARY_DIR}/LibAtticaConfig.cmake
              ${attica_BINARY_DIR}/LibAtticaConfigVersion.cmake
        DESTINATION ${LIB_DESTINATION}/cmake/LibAttica
       )

install(EXPORT LibAtticaExport FILE LibAtticaTargets.cmake
        DESTINATION ${LIB_DESTINATION}/cmake/LibAttica
        NAMESPACE LibAttica::)
