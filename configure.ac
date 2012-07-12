#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([guestos],[1.0],[abhaykadam88@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LIBTOOL

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lOpenCL':
AC_CHECK_LIB([OpenCL], [main])
# FIXME: Replace `main' with a function in `-laticalcl':
AC_CHECK_LIB([aticalcl], [main])
# FIXME: Replace `main' with a function in `-laticalrt':
AC_CHECK_LIB([aticalrt], [main])
# FIXME: Replace `main' with a function in `-ldl':
AC_CHECK_LIB([dl], [main])
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])
# FIXME: Replace `main' with a function in `-lncurses':
AC_CHECK_LIB([ncurses], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h float.h inttypes.h limits.h memory.h stddef.h stdint.h stdlib.h string.h sys/ioctl.h sys/socket.h sys/time.h unistd.h utime.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CHECK_MEMBERS([struct stat.st_blksize])
AC_STRUCT_ST_BLOCKS
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_CHOWN
AC_FUNC_ERROR_AT_LINE
AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([alarm bzero ftruncate getcwd gettimeofday memset mkdir munmap select socket strcasecmp strchr strdup strncasecmp strndup strtol utime])

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/libbio/Makefile
                 src/libcachesystem/Makefile
                 src/libdisasm/Makefile
                 src/libesim/Makefile
                 src/libfs/Makefile
                 src/libfs/bfs/Makefile
                 src/libfs/hostfs/Makefile
                 src/libgpudisasm/Makefile
                 src/libgpukernel/Makefile
                 src/libintr/Makefile
                 src/libm2skernel/Makefile
                 src/libmhandle/Makefile
                 src/libmisc/Makefile
                 src/libnetwork/Makefile
                 src/libopt/Makefile
                 src/libstruct/Makefile
                 src/libutils/Makefile])
AC_OUTPUT
