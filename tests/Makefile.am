.PHONY: build clean

ROOT=$(realpath ..)
BUILD_PATH=$(ROOT)/build
SUITES_PATH=$(realpath .)/suites
BIN_PATH=$(realpath .)/bin

CUSTOM_LIB=-L$(BUILD_PATH)/lib -lproto
CUSTOM_INCLUDES=-I$(BUILD_PATH)/include
CUSTOM_FLAGS=-g

build:
	mkdir -p bin
	$(CC) $(CUSTOM_FLAGS) $(SUITES_PATH)/test_arrays.c -o $(BIN_PATH)/test_arrays $(CUSTOM_INCLUDES) $(CUSTOM_LIB)
	$(CC) $(CUSTOM_FLAGS) $(SUITES_PATH)/test_data_types.c -o $(BIN_PATH)/test_data_types $(CUSTOM_INCLUDES) $(CUSTOM_LIB)
	$(CC) $(CUSTOM_FLAGS) $(SUITES_PATH)/test_objects.c -o $(BIN_PATH)/test_objects $(CUSTOM_INCLUDES) $(CUSTOM_LIB)
	$(CC) $(CUSTOM_FLAGS) $(SUITES_PATH)/test_generic_caller.c -o $(BIN_PATH)/test_generic_caller $(CUSTOM_INCLUDES) $(CUSTOM_LIB)

clean:
	rm -rf bin
	rm -f Makefile Makefile.in
	rm -f scripts/*.pyc
