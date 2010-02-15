
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Library directory name" FORCE)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH  TRUE)
set(CMAKE_INSTALL_RPATH "${LIB_DESTINATION}" )

find_package(Qt4 REQUIRED)
include_directories( ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} )

# mingw can't handle exported explicit template instantiations in a DLL
if (MINGW)
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols ${CMAKE_SHARED_LINKER_FLAGS}")
endif (MINGW)

configure_file(version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/version.h)

set(ocsclient_SRCS
   qtplatformdependent.cpp
   parser.cpp
   getjob.cpp
   atticabasejob.cpp
   itemjob.cpp
   listjob_inst.cpp
   downloaddescription.cpp
   eventparser.cpp
   event.cpp
   accountbalance.cpp
   accountbalanceparser.cpp
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
    VERSION ${CMAKE_LIBATTICA_VERSION_STRING}
    SOVERSION ${CMAKE_LIBATTICA_VERSION_MAJOR}
    LINK_INTERFACE_LIBRARIES ""
    DEFINE_SYMBOL ATTICA_LIB_MAKEDLL
)

target_link_libraries(attica ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY})


install(TARGETS attica ARCHIVE DESTINATION ${LIB_DESTINATION}
                               LIBRARY DESTINATION ${LIB_DESTINATION}
                               RUNTIME DESTINATION bin)

install(FILES
    activity.h
    accountbalance.h
    atticabasejob.h
    atticaclient_export.h
    content.h
    category.h
    downloaddescription.h
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
    #interface for external platform plugins
    platformdependent.h
    postjob.h
    providermanager.h
    provider.h
    ${CMAKE_CURRENT_BINARY_DIR}/version.h
    DESTINATION include/attica COMPONENT Devel
)

# Install package config file
if(NOT WIN32)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/libattica.pc.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/libattica.pc
    )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libattica.pc
        DESTINATION ${LIB_DESTINATION}/pkgconfig
    )
endif(NOT WIN32)

