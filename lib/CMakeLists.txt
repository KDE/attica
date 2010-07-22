
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
   accountbalance.cpp
   accountbalanceparser.cpp
   activity.cpp
   activityparser.cpp
   atticabasejob.cpp
   privatedata.cpp
   privatedataparser.cpp
   category.cpp
   categoryparser.cpp
   comment.cpp
   commentparser.cpp
   content.cpp
   contentparser.cpp
   downloaddescription.cpp
   downloaditem.cpp
   downloaditemparser.cpp
   event.cpp
   eventparser.cpp
   folder.cpp
   folderparser.cpp
   getjob.cpp
   itemjob.cpp
   knowledgebaseentry.cpp
   knowledgebaseentryparser.cpp
   license.cpp
   licenseparser.cpp
   listjob_inst.cpp
   message.cpp
   messageparser.cpp
   metadata.cpp
   parser.cpp
   person.cpp
   personparser.cpp
   postfiledata.cpp
   postjob.cpp
   provider.cpp
   providermanager.cpp
   qtplatformdependent.cpp
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
    comment.h
    commentparser.h
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
    license.h
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

# Add the optional subdirectory with unit tests
if (ATTICA_ENABLE_TESTS)
    add_subdirectory(tests)
endif (ATTICA_ENABLE_TESTS)

