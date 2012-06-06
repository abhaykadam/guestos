lib_LIBRARIES = libfs.a
libfs_a_SOURCES = fs.h \
		mount.h \
		dcache.h \
		filesystems.h \
		fdtable.h \
		path.h \
		namei.h \
		fs_struct.h \
		inode.c \
		namei.c \
		file.c \
		file_table.c

AM_CFLAGS = -Wall -fno-strict-aliasing -m32

INCLUDES = -I$(top_srcdir)/src/libutils/

