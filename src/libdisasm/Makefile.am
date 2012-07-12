noinst_LTLIBRARIES = libdisasm.la
libdisasm_la_SOURCES = \
	disasm.c \
	disasm.h \
	machine.dat

AM_CFLAGS = -Wall -fno-strict-aliasing

INCLUDES = -I$(top_srcdir)/src/libstruct \
	-I$(top_srcdir)/src/libmhandle

ACLOCAL_AMFLAGS = -I m4
