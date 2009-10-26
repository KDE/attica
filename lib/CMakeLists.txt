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
   personjob.cpp
   provider.cpp
   providermanager.cpp
   postjob.cpp
   postfiledata.cpp
   postjobstatus.cpp
   postjobstatusparser.cpp
   folder.cpp
   folderparser.cpp
   message.cpp
   messageparser.cpp
   category.cpp
   categoryparser.cpp
   content.cpp
   contentparser.cpp
   downloaditem.cpp
   downloaditemparser.cpp
   knowledgebaseentry.cpp
   knowledgebaseentryparser.cpp
)



kde4_add_library(ocsclient SHARED ${ocsclient_SRCS})
set_target_properties(ocsclient PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})

# FIXME: Remove KDE4 Libraries
target_link_libraries(ocsclient ${QT_QTCORE_LIBRARY} ${QT_QTNETWORK_LIBRARY} ${QT_QTGUI_LIBRARY} ${KDE4_KIO_LIBRARY})

install(TARGETS ocsclient ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    atticaclient_export.h
    content.h
    providermanager.h
    provider.h
    person.h
    personjob.h
    category.h
    itemjob.h
    listjob.h
    getjob.h
    postjob.h
    atticabasejob.h
    DESTINATION ${INCLUDE_INSTALL_DIR}/attica COMPONENT Devel
)



set(attica_kde_SRCS kdeinternals.cpp internals.cpp)
kde4_add_plugin(attica_kde ${attica_kde_SRCS})

target_link_libraries(attica_kde ${KDE4_KIO_LIBS} ${QT_QTMAIN_LIBRARY} ${QT_QTCORE_LIBRARY})

# FIXME: Use a more sane destination
install(TARGETS attica_kde DESTINATION "~")
