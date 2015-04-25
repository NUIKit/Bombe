AC_PREREQ(2.59)
AC_INIT([libBombe], [0.1], [devteam.codafi@gmail.com], [libBombe])
AC_REVISION([$$])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADER([config/config.h])
AC_CONFIG_MACRO_DIR([m4])
ac_clean_files=a.out.dSYM
AM_MAINTAINER_MODE

AC_PROG_CC([clang gcc cc])
AC_PROG_CXX([clang++ g++ c++])
AC_PROG_OBJC([clang gcc cc])

AC_USE_SYSTEM_EXTENSIONS
AM_INIT_AUTOMAKE([foreign no-dependencies])
LT_INIT([disable-static])

#
## Checks for header files.
#
AC_HEADER_STDC
AC_CHECK_HEADERS([TargetConditionals.h fcntl.h malloc/malloc.h libkern/OSCrossEndian.h libkern/OSAtomic.h])

#
## Checks for mach.
#
AC_CHECK_HEADER([mach/mach.h], [
  AC_DEFINE(HAVE_MACH, 1, [Define if mach is present])
  have_mach=true], [have_mach=false]
)

#
## Generate Makefiles.
#
AC_CONFIG_FILES([Makefile Bombe/Makefile src/Makefile])
AC_OUTPUT

