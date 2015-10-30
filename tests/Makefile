# tests Makefile

include ../Makefile.am

ROOT=$(realpath ..)
INCLUDEPATH=$(ROOT)
SUITES_PATH=$(realpath .)/suites
TESTSBINPATH=$(realpath .)/bin

CC=gcc
CC_INCLUDES=-I$(INCLUDEPATH)
CC_SOURCES=$(INCLUDEPATH)/proto.c
CC_LIBRARIES=
CC_FLAGS=-g

.PHONY: build clean

build:
	mkdir -p $(TESTSBINPATH)
	$(CC) $(CC_FLAGS) $(SUITES_PATH)/test_data_types.c -o $(TESTSBINPATH)/test_data_types $(CC_INCLUDES) $(CC_LIBRARIES) $(CC_SOURCES)
	$(CC) $(CC_FLAGS) $(SUITES_PATH)/test_objects.c -o $(TESTSBINPATH)/test_objects $(CC_INCLUDES) $(CC_LIBRARIES) $(CC_SOURCES)

clean:
	rm -rf $(TESTSBINPATH)
