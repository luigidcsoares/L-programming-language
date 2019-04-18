# Defining OS specific configs.
ifeq ($(OS), Windows_NT)
    # Executable.
    export EXEC = lc.exe
else 
    # Executable.
    export EXEC = lc
endif

# Directories.
export ROOT_DIR  = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export INC_DIR   = $(ROOT_DIR)include/
export SRC_DIR   = $(ROOT_DIR)src/
export BUILD_DIR = $(ROOT_DIR)build/

# Compiler options.
export CXXFLAGS = -std=c++17 -I $(INC_DIR)

all:
	-mkdir "$(BUILD_DIR)"
	cd "$(SRC_DIR)" && $(MAKE) all
	@echo "========== Compilation finished =========="
