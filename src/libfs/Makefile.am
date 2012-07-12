SUBDIRS = \
	bfs \
	hostfs

noinst_LTLIBRARIES = libfs.la
libfs_la_SOURCES = \
		fs.h \
		mount.h \
		dcache.h \
		fdtable.h \
		path.h \
		namei.h \
		fs_struct.h \
		buffer_head.h \
		bdev.h \
		filesystem.h \
		bdev.c \
		inode.c \
		file.c \
		filesystem.c \
		mount.c

AM_CFLAGS = -Wall -fno-strict-aliasing

INCLUDES = \
	   -I$(top_srcdir)/src/libbio \
	   -I$(top_srcdir)/src/libutils \
	   -I$(top_srcdir)/src/libfs/hostfs \
	   -I$(top_srcdir)/src/libfs/bfs

libfs_LADD = \
	$(top_builddir)/src/libfs/bfs/libbfs.la \
	$(top_builddir)/src/libfs/hostfs/libbfs.la

ACLOCAL_AMFLAGS = -I m4
