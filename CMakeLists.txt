cmake_minimum_required(VERSION 3.0)

set(KF5_VERSION "5.31.0") # handled by release scripts
project(Attica VERSION ${KF5_VERSION})

# ECM setup
include(FeatureSummary)
find_package(ECM 5.31.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://projects.kde.org/projects/kdesupport/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers) # Used to create CMake config files
include(ECMQtDeclareLoggingCategory)
include(KDEInstallDirs) # Used to set installation paths
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)


ecm_setup_version(PROJECT
    VARIABLE_PREFIX ATTICA
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/attica_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5AtticaConfigVersion.cmake"
    SOVERSION 5)

# Dependencies
set(REQUIRED_QT_VERSION 5.6.0)

# Required Qt5 components to build this framework
find_package(Qt5 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Core Network)

set(ATTICA_LIB_SONAME KF5Attica)

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
configure_package_config_file(
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

