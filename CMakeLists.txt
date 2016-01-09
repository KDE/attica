cmake_minimum_required(VERSION 2.8.12)

project(Attica)

# ECM setup
include(FeatureSummary)
find_package(ECM 5.18.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://projects.kde.org/projects/kdesupport/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMPackageConfigHelpers) # Used to create CMake config files
include(KDEInstallDirs) # Used to set installation paths
include(KDEFrameworkCompilerSettings)
include(KDECMakeSettings)

set(KF5_VERSION "5.19.0") # handled by release scripts

ecm_setup_version(${KF5_VERSION}
    VARIABLE_PREFIX ATTICA
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/attica_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5AtticaConfigVersion.cmake"
    SOVERSION 5)

# Dependencies
set(REQUIRED_QT_VERSION "5.3.0")

# Required Qt5 components to build this framework
find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Core Network)

set(ATTICA_LIB_SONAME KF5Attica)
set(ATTICA_LIB_SONAME_CAMEL KF5Attica)
set(ATTICA_LIB_NAMESPACE KF5)

#if(NOT MSVC)
    #set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -Wall -Wno-switch -O2 -g")
    #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Wall -Wno-switch -O2")
    #set(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS} -Wall -Wno-switch -g3 -ggdb -O0" CACHE STRING "Debug options." FORCE)
#endif(NOT MSVC)

add_definitions( -DQT_NO_CAST_FROM_ASCII )
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

# Enable static build
option(ATTICA_STATIC_BUILD "Build a static library" Off)

add_subdirectory(src)

# Enable unit testing
if (BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif ()

# Create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5Attica")

# Create the CMake Config files
ecm_configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5AtticaConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5AtticaConfig.cmake"
    INSTALL_DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
)

install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/KF5AtticaConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/KF5AtticaConfigVersion.cmake"
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel)

install(EXPORT KF5AtticaTargets
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        FILE KF5AtticaTargets.cmake
        NAMESPACE KF5::)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/attica_version.h"
        DESTINATION "${KDE_INSTALL_INCLUDEDIR_KF5}"
        COMPONENT Devel)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

