include(ECMMarkAsTest)

find_package(Qt${QT_MAJOR_VERSION}Widgets ${REQUIRED_QT_VERSION} CONFIG REQUIRED)
set_package_properties(Qt${QT_MAJOR_VERSION}Widgets PROPERTIES PURPOSE "Required for tests")

add_executable(projecttest)
ecm_mark_as_test(projecttest)

set(editproject_UI_H)
qt_wrap_ui(editproject_UI_H editproject.ui)

target_sources(projecttest PRIVATE
    projecttest.cpp
    main.cpp
    ${editproject_UI_H}
)

target_link_libraries(projecttest Qt${QT_MAJOR_VERSION}::Widgets KF5::Attica)
