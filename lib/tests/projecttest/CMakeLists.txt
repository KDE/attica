project(projecttest)
cmake_minimum_required(VERSION 2.8)

set(QT_MIN_VERSION "4.7.0")
if (Qt5Core_FOUND)
    find_package(Qt5Transitional REQUIRED
        Widgets
    )
endif()

include_directories(${KDE4_INCLUDES}
                    ${QT_INCLUDES}
                    ${LIBATTICA_INCLUDE_DIRS}
                    ${CMAKE_CURRENT_BINARY_DIR} )

set(editproject_UI editproject.ui)
QT4_WRAP_UI(editproject_UI_H ${editproject_UI})

set(projecttest_SRCS
    projecttest.cpp
    main.cpp
)
qt4_automoc(${projecttest_SRCS} ${editproject_SRCS})

add_executable(projecttest ${projecttest_SRCS} ${editproject_UI_H})

target_link_libraries(projecttest ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} attica)
