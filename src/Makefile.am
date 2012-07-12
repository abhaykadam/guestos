SUBDIRS = \
	libbio \
	libfs \
	libutils \
	libmhandle \
	libstruct \
	libopt \
	libmisc \
	libm2skernel \
	libdisasm \
	libesim \
	libnetwork \
	libcachesystem \
	libgpukernel \
	libgpudisasm \
	libintr

bin_PROGRAMS = \
	guestos 

guestos_SOURCES = \
	guestos.c

INCLUDES = \
	-I$(top_srcdir)/src/libbio \
	-I$(top_srcdir)/src/libfs \
	-I$(top_srcdir)/src/libutils \
	-I$(top_srcdir)/src/libmhandle \
	-I$(top_srcdir)/src/libstruct \
	-I$(top_srcdir)/src/libopt \
	-I$(top_srcdir)/src/libmisc \
	-I$(top_srcdir)/src/libm2skernel \
	-I$(top_srcdir)/src/libdisasm \
	-I$(top_srcdir)/src/libesim \
	-I$(top_srcdir)/src/libnetwork \
	-I$(top_srcdir)/src/libcachesystem \
	-I$(top_srcdir)/src/libgpukernel \
	-I$(top_srcdir)/src/libgpudisasm \
	-I$(top_srcdir)/src/libintr

guestos_LDADD = \
	$(top_builddir)/src/libm2skernel/libm2skernel.la \
	$(top_builddir)/src/libdisasm/libdisasm.la \
        $(top_builddir)/src/libopt/libopt.la \
	$(top_builddir)/src/libmisc/libmisc.la \
	$(top_builddir)/src/libcachesystem/libcachesystem.la \
	$(top_builddir)/src/libgpukernel/libgpukernel.la \
	$(top_builddir)/src/libgpudisasm/libgpudisasm.la \
	$(top_builddir)/src/libnetwork/libnetwork.la \
	$(top_builddir)/src/libesim/libesim.la \
	$(top_builddir)/src/libstruct/libstruct.la \
	$(top_builddir)/src/libmhandle/libmhandle.la \
	$(top_builddir)/src/libutils/libutils.la \
	$(top_builddir)/src/libbio/libbio.la \
	$(top_builddir)/src/libfs/libfs.la \
	$(top_builddir)/src/libintr/libintr.la \
	-lm -lpthread

AM_CFLAGS = -Wall -fno-strict-aliasing
AM_LDFLAGS = #-static


ACLOCAL_AMFLAGS = -I m4

