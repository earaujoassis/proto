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

.PHONY: tests clean

tests:
	$(MAKE) -C tests build

clean:
	$(MAKE) -C tests clean
