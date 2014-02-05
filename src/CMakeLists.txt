# mingw can't handle exported explicit template instantiations in a DLL
if (MINGW)
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols ${CMAKE_SHARED_LINKER_FLAGS}")
endif (MINGW)

configure_file(version.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/version.h)
configure_file(atticaclient_export.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/atticaclient_export.h)
# TODO: use generate_export_header?

set(attica_SRCS
   accountbalance.cpp
   accountbalanceparser.cpp
   achievement.cpp
   achievementparser.cpp
   buildservice.cpp
   buildserviceparser.cpp
   buildservicejob.cpp
   buildservicejobparser.cpp
   buildservicejoboutput.cpp
   buildservicejoboutputparser.cpp
   activity.cpp
   activityparser.cpp
   atticabasejob.cpp
   atticautils.cpp
   privatedata.cpp
   privatedataparser.cpp
   category.cpp
   categoryparser.cpp
   comment.cpp
   commentparser.cpp
   content.cpp
   contentparser.cpp
   deletejob.cpp
   distribution.cpp
   distributionparser.cpp
   downloaddescription.cpp
   downloaditem.cpp
   downloaditemparser.cpp
   event.cpp
   eventparser.cpp
   folder.cpp
   folderparser.cpp
   forum.cpp
   forumparser.cpp
   getjob.cpp
   homepageentry.cpp
   homepagetype.cpp
   homepagetypeparser.cpp
   icon.cpp
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
   platformdependent_v2.cpp
   postfiledata.cpp
   postjob.cpp
   project.cpp
   projectparser.cpp
   putjob.cpp
   remoteaccount.cpp
   remoteaccountparser.cpp
   provider.cpp
   providermanager.cpp
   publisher.cpp
   publisherparser.cpp
   publisherfield.cpp
   publisherfieldparser.cpp
   qtplatformdependent.cpp
   topic.cpp
   topicparser.cpp
)

if (ATTICA_STATIC_BUILD)
    add_library(KF5Attica STATIC ${attica_SRCS})
    set_target_properties(KF5Attica PROPERTIES
        VERSION ${ATTICA_VERSION_STRING}
        SOVERSION ${ATTICA_VERSION_MAJOR}
    )
else (ATTICA_STATIC_BUILD)
    add_library(KF5Attica SHARED ${attica_SRCS})
    set_target_properties(KF5Attica PROPERTIES
        VERSION ${ATTICA_VERSION_STRING}
        SOVERSION ${ATTICA_VERSION_MAJOR}.${ATTICA_VERSION_MINOR}
        DEFINE_SYMBOL ATTICA_LIB_MAKEDLL
    )
endif(ATTICA_STATIC_BUILD)

add_library(KF5::Attica ALIAS KF5Attica)

# OUCH?
set_property(TARGET KF5Attica APPEND PROPERTY COMPILE_DEFINITIONS QT_DISABLE_DEPRECATED_BEFORE=0)

target_link_libraries(KF5Attica
PUBLIC
  Qt5::Core
  Qt5::Network
)
target_include_directories(KF5Attica INTERFACE $<INSTALL_INTERFACE:${INCLUDE_DESTINATION}/KF5Attica>)
set_target_properties(KF5Attica
    PROPERTIES VERSION ${ATTICA_VERSION_STRING}
    SOVERSION ${ATTICA_SOVERSION}
    EXPORT_NAME "Attica"
)

install(TARGETS KF5Attica
        EXPORT KF5AtticaTargets
        ${INSTALL_TARGETS_DEFAULT_ARGS})


ecm_generate_headers(
    Activity
    # TODO: other classes

    MODULE_NAME Attica
    REQUIRED_HEADERS Attica_HEADERS
)

install(FILES
    activity.h
    accountbalance.h
    achievement.h
    atticabasejob.h
    ${CMAKE_CURRENT_BINARY_DIR}/atticaclient_export.h
    atticautils.h
    comment.h
    content.h
    category.h
    deletejob.h
    distribution.h
    downloaddescription.h
    downloaditem.h
    event.h
    folder.h
    forum.h
    getjob.h
    homepageentry.h
    homepagetype.h
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
    ${Attica_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/version.h
    DESTINATION ${INCLUDE_DESTINATION}/Attica
    COMPONENT Devel
)

include(ECMGeneratePriFile)
ecm_generate_pri_file(
    BASE_NAME Attica
    LIB_NAME KF5Attica
    DEPS "core"
    FILENAME_VAR PRI_FILENAME
)
install(FILES ${PRI_FILENAME}
        DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


# Install package config file
if(NOT WIN32)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/libKF5Attica.pc.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/libKF5Attica.pc
    )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libKF5Attica.pc
        DESTINATION ${LIB_DESTINATION}/pkgconfig
    )
endif(NOT WIN32)

