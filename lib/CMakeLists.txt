
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
   accountbalancexmlparser.cpp
   achievement.cpp
   achievementxmlparser.cpp
   buildservice.cpp
   buildservicexmlparser.cpp
   buildservicejob.cpp
   buildservicejobxmlparser.cpp
   buildservicejoboutput.cpp
   buildservicejoboutputxmlparser.cpp
   activity.cpp
   activityxmlparser.cpp
   atticabasejob.cpp
   atticautils.cpp
   privatedata.cpp
   privatedataxmlparser.cpp
   category.cpp
   categoryxmlparser.cpp
   comment.cpp
   commentxmlparser.cpp
   content.cpp
   contentxmlparser.cpp
   deletejob.cpp
   distribution.cpp
   distributionxmlparser.cpp
   downloaddescription.cpp
   downloaditem.cpp
   downloaditemxmlparser.cpp
   event.cpp
   eventxmlparser.cpp
   folder.cpp
   folderxmlparser.cpp
   forum.cpp
   forumxmlparser.cpp
   getjob.cpp
   homepageentry.cpp
   homepagetype.cpp
   homepagetypexmlparser.cpp
   icon.cpp
   itemjob.cpp
   knowledgebaseentry.cpp
   knowledgebaseentryxmlparser.cpp
   license.cpp
   licensexmlparser.cpp
   listjob_inst.cpp
   message.cpp
   messagexmlparser.cpp
   metadata.cpp
   parser.cpp
   parserfactory.cpp
   parserfactory_inst.cpp
   person.cpp
   personxmlparser.cpp
   platformdependent_v2.cpp
   postfiledata.cpp
   postjob.cpp
   project.cpp
   projectxmlparser.cpp
   putjob.cpp
   remoteaccount.cpp
   remoteaccountxmlparser.cpp
   provider.cpp
   providermanager.cpp
   publisher.cpp
   publisherxmlparser.cpp
   publisherfield.cpp
   publisherfieldxmlparser.cpp
   qtplatformdependent.cpp
   topic.cpp
   topicxmlparser.cpp
   xmlparser.cpp
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
    atticabasejob.h
    ${CMAKE_CURRENT_BINARY_DIR}/atticaclient_export.h
    atticautils.h
    comment.h
    #commentparser.h
    content.h
    category.h
    deletejob.h
    distribution.h
    #distributionparser.h
    downloaddescription.h
    downloaditem.h
    event.h
    folder.h
    forum.h
    getjob.h
    homepageentry.h
    homepagetype.h
    #homepagetypeparser.h
    icon.h
    itemjob.h
    knowledgebaseentry.h
    listjob.h
    license.h
    message.h
    metadata.h
    person.h
    #interface for external platform plugins
    platformdependent.h
    platformdependent_v2.h
    privatedata.h
    postjob.h
    project.h
    putjob.h
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

