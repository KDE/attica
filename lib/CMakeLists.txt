
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
set(LIB_DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE STRING "Library directory name" FORCE)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH  TRUE)

find_package(Qt4 REQUIRED)
include_directories( ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} )

# mingw can't handle exported explicit template instantiations in a DLL
if (MINGW)
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols ${CMAKE_SHARED_LINKER_FLAGS}")
endif (MINGW)

configure_file(version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/version.h)
configure_file(atticaclient_export.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/atticaclient_export.h)

set(ocsclient_SRCS
   accountbalance.cpp
   achievement.cpp
   basicjob.cpp
   buildservice.cpp
   buildservicejob.cpp
   buildservicejoboutput.cpp
   activity.cpp
   atticautils.cpp
   privatedata.cpp
   category.cpp
   comment.cpp
   content.cpp
   distribution.cpp
   downloaddescription.cpp
   downloaditem.cpp
   event.cpp
   folder.cpp
   forum.cpp
   homepageentry.cpp
   homepagetype.cpp
   icon.cpp
   iparser.cpp
   job.cpp
   job_inst.cpp
   knowledgebaseentry.cpp
   license.cpp
   message.cpp
   metadata.cpp
   person.cpp
   platformdependent.cpp
   postfiledata.cpp
   project.cpp
   remoteaccount.cpp
   provider.cpp
   providermanager.cpp
   publisher.cpp
   publisherfield.cpp
   qtplatformdependent.cpp
   topic.cpp
   xmlparserv2.cpp
)

qt4_automoc(${ocsclient_SRCS})

if (ATTICA_STATIC_BUILD)
    add_library(attica STATIC ${ocsclient_SRCS})
    set_target_properties(attica PROPERTIES
        VERSION ${CMAKE_LIBATTICA_VERSION_STRING}
        SOVERSION ${CMAKE_LIBATTICA_VERSION_MAJOR}
    )
else (ATTICA_STATIC_BUILD)
    add_library(attica SHARED ${ocsclient_SRCS})
    set_target_properties(attica PROPERTIES
        VERSION ${CMAKE_LIBATTICA_VERSION_STRING}
        SOVERSION ${CMAKE_LIBATTICA_VERSION_MAJOR}.${CMAKE_LIBATTICA_VERSION_MINOR}
        LINK_INTERFACE_LIBRARIES ""
        DEFINE_SYMBOL ATTICA_LIB_MAKEDLL
    )
endif(ATTICA_STATIC_BUILD)
target_link_libraries(attica ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY})


install(TARGETS attica ARCHIVE DESTINATION ${LIB_DESTINATION}
                               LIBRARY DESTINATION ${LIB_DESTINATION}
                               RUNTIME DESTINATION bin)

install(FILES
    activity.h
    accountbalance.h
    achievement.h
    ${CMAKE_CURRENT_BINARY_DIR}/atticaclient_export.h
    atticautils.h
    comment.h
    content.h
    category.h
    distribution.h
    downloaddescription.h
    downloaditem.h
    event.h
    folder.h
    forum.h
    homepageentry.h
    homepagetype.h
    icon.h
    job.h
    knowledgebaseentry.h
    license.h
    message.h
    metadata.h
    nonetype.h
    person.h
    #interface for external platform plugins
    platformdependent.h
    privatedata.h
    project.h
    remoteaccount.h
    buildservice.h
    buildservicejob.h
    buildservicejoboutput.h
    providermanager.h
    provider.h
    publisher.h
    publisherfield.h
    topic.h
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

