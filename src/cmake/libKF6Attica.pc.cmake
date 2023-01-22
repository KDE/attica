prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}
libdir=@KDE_INSTALL_FULL_LIBDIR@
includedir=@KDE_INSTALL_FULL_INCLUDEDIR@

Name: lib@ATTICA_LIB_SONAME@
Description: Qt library to access Open Collaboration Services
URL: https://www.kde.org
Requires: Qt6Core Qt6Network
Version: @ATTICA_VERSION@
Libs: -L@KDE_INSTALL_FULL_LIBDIR@ -l@ATTICA_LIB_SONAME@
Cflags: -I@KDE_INSTALL_FULL_INCLUDEDIR_KF@/Attica
