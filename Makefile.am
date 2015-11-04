EXTRA_DIST = proto.def README.md LICENSE

include_HEADERS = proto.h
lib_LTLIBRARIES = libproto.la
libproto_la_SOURCES = \
	config.h \
	array.c \
	data_types.c \
	functions.c \
	object.c
libproto_la_LDFLAGS = \
	-no-undefined \
	-export-symbols-regex '^proto_' \
	-version-info 11:0:7

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = proto.pc

.PHONY: tests clean

tests:
	$(MAKE) -C tests build

clean:
	$(MAKE) -C tests clean
	rm -rf .deps
	rm -rf .libs
	rm -rf autom4te.cache
	rm -rf build
	rm -rf m4
	rm -f .DS_Store *.lo *.o aclocal.m4 autoscan.log
	rm -f compile config.guess config.h config.h.in~ config.log config.status config.sub configure
	rm -f depcomp install-sh libproto.la libtool ltmain.sh
	rm -f Makefile Makefile.in missing proto.pc stamp-h1
