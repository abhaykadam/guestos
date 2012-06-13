lib_LIBRARIES = libbfs.a
libbfs_a_SOURCES = \
		bfs_fs.h \
		bfs_super.c \
		bfs_fs_sb.h \
		bfs.h \
		inode.c

AM_CFLAGS = -Wall -fno-strict-aliasing -m32

INCLUDES = -I$(top_srcdir)/src/libutils \
	   -I$(top_srcdir)/src/libfs \
	   -I$(top_srcdir)/src/libbio
