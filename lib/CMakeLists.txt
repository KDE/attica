set(attica_SRCS
   attica.cpp
   main.cpp
   atticaview.cpp
   personplate.cpp
   person.cpp
   personjob.cpp
   personparser.cpp
   personlistjob.cpp
   detailsview.cpp
   peopleview.cpp
   activity.cpp
   activityparser.cpp
   activitylistjob.cpp
   activityview.cpp
 )

kde4_add_ui_files(attica_SRCS prefs_base.ui)

kde4_add_kcfg_files(attica_SRCS settings.kcfgc )

kde4_add_executable(attica ${attica_SRCS})

target_link_libraries(attica ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS}
  ${KDE4_KABC_LIBS})

install(TARGETS attica DESTINATION ${BIN_INSTALL_DIR} )


########### install files ###############

install( FILES attica.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR} )
install( FILES attica.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES atticaui.rc  DESTINATION  ${DATA_INSTALL_DIR}/attica )
