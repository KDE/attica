include(ECMMarkAsTest)

find_package(Qt5Widgets ${REQUIRED_QT_VERSION} CONFIG REQUIRED)
set_package_properties(Qt5Widgets PROPERTIES PURPOSE "Required for tests")

add_executable(projecttest)
ecm_mark_as_test(projecttest)

set(editproject_UI_H)
qt_wrap_ui(editproject_UI_H editproject.ui)

target_sources(projecttest PRIVATE
    projecttest.cpp
    main.cpp
    ${editproject_UI_H}
)

target_link_libraries(projecttest Qt5::Widgets KF5::Attica)
