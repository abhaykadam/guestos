noinst_LTLIBRARIES = libhostfs.la
libhostfs_la_SOURCES = \
		hostfs_super.h \
		hostfs_super.c \
		hostfs.h

AM_CFLAGS = -Wall -fno-strict-aliasing

INCLUDES = -I$(top_srcdir)/src/libutils \
	   -I$(top_srcdir)/src/libfs

ACLOCAL_AMFLAGS = -I m4
