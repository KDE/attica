set(atticaclient_SRCS
   activity.cpp
   activityparser.cpp
   activitylistjob.cpp
   person.cpp
   personparser.cpp
   personjob.cpp
   personlistjob.cpp
   ocsapi.cpp
   postjob.cpp
 )

kde4_add_library(atticaclient SHARED ${atticaclient_SRCS})
set_target_properties(atticaclient PROPERTIES VERSION ${KDE_GENERIC_LIB_VERSION} SOVERSION ${KDE_GENERIC_LIB_SOVERSION})

target_link_libraries(atticaclient ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KABC_LIBS})

install(TARGETS atticaclient DESTINATION ${LIB_INSTALL_DIR})
