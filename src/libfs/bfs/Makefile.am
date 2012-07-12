noinst_LTLIBRARIES = libbfs.la
libbfs_la_SOURCES = \
		bfs_fs.h \
		bfs_super.h \
		bfs_fs_sb.h \
		bfs.h \
		bfs_super.c \
		inode.c

AM_CFLAGS = -Wall -fno-strict-aliasing

INCLUDES = -I$(top_srcdir)/src/libutils \
	   -I$(top_srcdir)/src/libfs \
	   -I$(top_srcdir)/src/libbio

ACLOCAL_AMFLAGS = -I m4
