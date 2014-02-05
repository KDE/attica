cmake_minimum_required(VERSION 2.8.11)

find_package(Qt5Widgets CONFIG)

if (Qt5Widgets_FOUND)

set(editproject_UI editproject.ui)
qt5_wrap_ui(editproject_UI_H ${editproject_UI})

set(projecttest_SRCS
    projecttest.cpp
    main.cpp
)

add_executable(projecttest ${projecttest_SRCS} ${editproject_UI_H})

target_link_libraries(projecttest Qt5::Widgets ${ATTICA_LIB_SONAME})

endif()
