



IF (NOT WIN32)
   INCLUDE(FindPkgConfig REQUIRED)
   pkg_check_modules(ATTICA REQUIRED libattica )
ENDIF (NOT WIN32)

