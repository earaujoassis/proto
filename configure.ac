AC_PREREQ([2.69])
AC_INIT([proto], [0.9], [earaujoassis@gmail.com])

AC_CONFIG_AUX_DIR([.])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.10 foreign])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_SRCDIR([object.c])

AC_PROG_CC
AC_PROG_LIBTOOL

AC_CHECK_HEADERS([stddef.h stdio.h stdlib.h string.h stdbool.h stdarg.h])

AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_CONFIG_FILES([proto.pc
                 Makefile
                 tests/Makefile])
AC_OUTPUT
