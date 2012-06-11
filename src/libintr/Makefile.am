lib_LIBRARIES = libintr.a
libintr_a_SOURCES = \
		pic.h \
		isr.h \
		pic.c \
		isr.c \
		intr.c

AM_CFLAGS = -Wall -fno-strict-aliasing -m32

INCLUDES = \
	-I$(top_srcdir)/src/libm2skernel \
	-I$(top_srcdir)/src/libmhandle \
	-I$(top_srcdir)/src/libstruct \
	-I$(top_srcdir)/src/libmisc \
	-I$(top_srcdir)/src/libdisasm \
	-I$(top_srcdir)/src/libgpukernel \
	-I$(top_srcdir)/src/libfs \
	-I$(top_srcdir)/src/libutils
