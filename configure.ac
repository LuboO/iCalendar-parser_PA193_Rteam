AC_CONFIG_MACRO_DIR([m4])

AC_INIT([ical-parser], [0.1], [])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_SILENT_RULES([yes])

AC_ARG_ENABLE([debug], [AS_HELP_STRING([--enable-debug], [compile in debug mode])], [CXXFLAGS="-g -O2 -DDEBUG $CXXFLAGS"], [CXXFLAGS="-O2 $CXXFLAGS"])

AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT
