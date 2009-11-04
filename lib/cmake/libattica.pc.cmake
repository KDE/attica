prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=${CMAKE_INSTALL_PREFIX}/bin
libdir=${LIB_DESTINATION}
includedir=${CMAKE_INSTALL_PREFIX}/include

Name: libattica
Description: Qt library to access Open Collaboration Services
#Requires:
Version: ${ATTICA_VERSION_MAJOR}.${ATTICA_VERSION_MINOR}.${ATTICA_VERSION_PATCH}
Libs: -L${LIB_DESTINATION} -lattica
Cflags: -I${CMAKE_INSTALL_PREFIX}/include

