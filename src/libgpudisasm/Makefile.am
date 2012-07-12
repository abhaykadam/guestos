noinst_LTLIBRARIES = libgpudisasm.la
libgpudisasm_la_SOURCES = \
	gpudisasm.c \
	gpudisasm.dat \
	gpudisasm.h \
	gpudump.c

AM_CFLAGS = -Wall -fno-strict-aliasing -DMHANDLE

INCLUDES = -I$(top_srcdir)/src/libstruct \
	-I$(top_srcdir)/src/libmhandle \
	-I$(top_srcdir)/src/libmisc

ACLOCAL_AMFLAGS = -I m4
