prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${CMAKE_INSTALL_PREFIX}/bin
libdir=${LIB_DESTINATION}
includedir=${CMAKE_INSTALL_PREFIX}/include

Name: libattica
Description: Qt library to access Open Collaboration Services
#Requires:
Version: ${CMAKE_LIBATTICA_VERSION_MAJOR}.${CMAKE_LIBATTICA_VERSION_MINOR}.${CMAKE_LIBATTICA_VERSION_PATCH}
Libs: -L${LIB_DESTINATION} -lattica
Cflags: -I${CMAKE_INSTALL_PREFIX}/include

