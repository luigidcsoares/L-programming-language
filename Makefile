# Defining exec file extension.
ifeq ($(OS), Windows_NT)
    export EXEC = lc.exe
else
    export EXEC = lc

# Directories.
export INC_DIR   = $(CURDIR)/include
export SRC_DIR   = $(CURDIR)/src
export BUILD_DIR = $(CURDIR)/build

# Compiler options.
export CXXFLAGS = -std=c++17 -I $(INC_DIR)

all:
	mkdir -p $(BUILD_DIR)
	cd $(SRC_DIR) && $(MAKE) all
