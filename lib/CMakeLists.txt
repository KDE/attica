set(atticaclient_SRCS
   activity.cpp
   activityparser.cpp
   activitylistjob.cpp
   person.cpp
   personparser.cpp
   personjob.cpp
   personlistjob.cpp
 )

kde4_add_library(atticaclient ${atticaclient_SRCS})

target_link_libraries(atticaclient ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_KABC_LIBS})
