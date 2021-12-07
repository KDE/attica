include(ECMAddTests)

find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Test)
set_package_properties(Qt${QT_MAJOR_VERSION}Test PROPERTIES PURPOSE "Required for autotests")

ecm_add_tests(
  configtest.cpp
  persontest.cpp
  providertest.cpp
  LINK_LIBRARIES Qt${QT_MAJOR_VERSION}::Test KF5::Attica
)
