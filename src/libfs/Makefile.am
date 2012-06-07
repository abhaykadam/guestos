SUBDIRS = \
	bfs \
	hostfs

lib_LIBRARIES = libfs.a
libfs_a_SOURCES = fs.h \
		mount.h \
		dcache.h \
		fdtable.h \
		path.h \
		namei.h \
		fs_struct.h \
		inode.c \
		file.c \
		mount.c

AM_CFLAGS = -Wall -fno-strict-aliasing -m32

INCLUDES = -I$(top_srcdir)/src/libutils \
	   -I$(top_srcdir)/src/libfs/hostfs

