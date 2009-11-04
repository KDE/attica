project(attica)

set(ATTICA_VERSION_MAJOR 0 CACHE INT "Major Attica version number" FORCE)
set(ATTICA_VERSION_MINOR 1 CACHE INT "Minor Attica version number" FORCE)
set(ATTICA_VERSION_PATCH 0 CACHE INT "Release Attica version number" FORCE)
set(ATTICA_VERSION_STRING "${ATTICA_VERSION_MAJOR}.${ATTICA_VERSION_MINOR}.${ATTICA_VERSION_PATCH}" CACHE STRING "Attica version string" FORCE)

cmake_minimum_required(VERSION 2.6)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" CACHE STRING "Library directory name" FORCE)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH  TRUE)
set(CMAKE_INSTALL_RPATH "${LIB_DESTINATION}" )

find_package(Qt4 REQUIRED)
include_directories( ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} )

set(ocsclient_SRCS
   internals.cpp
   qtinternals.cpp
   parser.cpp
   getjob.cpp
   atticabasejob.cpp
   itemjob.cpp
   listjob_inst.cpp
   eventparser.cpp
   event.cpp
   activity.cpp
   activityparser.cpp
   person.cpp
   personparser.cpp
   provider.cpp
   providermanager.cpp
   postjob.cpp
   postfiledata.cpp
   folder.cpp
   folderparser.cpp
   message.cpp
   messageparser.cpp
   metadata.cpp
   category.cpp
   categoryparser.cpp
   content.cpp
   contentparser.cpp
   downloaditem.cpp
   downloaditemparser.cpp
   knowledgebaseentry.cpp
   knowledgebaseentryparser.cpp
)

qt4_automoc(${ocsclient_SRCS})

add_library(attica SHARED ${ocsclient_SRCS})

set_target_properties(attica PROPERTIES
    VERSION ${ATTICA_VERSION_STRING}
    SOVERSION ${ATTICA_VERSION_MAJOR}
    LINK_INTERFACE_LIBRARIES ""
    DEFINE_SYMBOL MAKE_ATTICA_LIB
)

target_link_libraries(attica ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTGUI_LIBRARY})


install(TARGETS attica ARCHIVE DESTINATION ${LIB_DESTINATION}
                               LIBRARY DESTINATION ${LIB_DESTINATION}
                               RUNTIME DESTINATION bin)

install(FILES
    activity.h
    atticabasejob.h
    atticaclient_export.h
    content.h
    category.h
    downloaditem.h
    event.h
    folder.h
    getjob.h
    itemjob.h
    knowledgebaseentry.h
    listjob.h
    message.h
    metadata.h
    person.h
    postjob.h
    providermanager.h
    provider.h
    DESTINATION include/attica COMPONENT Devel
)


find_package(KDE4)

if (NOT KDE4_FOUND)
    message("** No KDE4 found, building attica without KDE4 plugin.")
endif (NOT KDE4_FOUND)
if (KDE4_FOUND)
    message("** KDE4 found, building attica with KDE4 plugin.")

    include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} )

    include(KDE4Defaults)
    include(MacroLibrary)
    include(MacroOptionalAddSubdirectory)

    set(attica_kde_SRCS
        kdeinternals.cpp
        internals.cpp
    )

    kde4_add_plugin(attica_kde ${attica_kde_SRCS})
    target_link_libraries(attica_kde ${KDE4_KIO_LIBS} ${QT_QTMAIN_LIBRARY} ${QT_QTCORE_LIBRARY})
    install(TARGETS attica_kde  EXPORT kdelibsLibraryTargets ${INSTALL_TARGETS_DEFAULT_ARGS})
endif (KDE4_FOUND)
