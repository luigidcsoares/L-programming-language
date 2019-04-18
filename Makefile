# Defining OS specific configs.
ifeq ($(OS), Windows_NT)
    # Executable.
    export EXEC = lc.exe

    # Function for fixing path separator.
    FixPath = $(subst /,\,$1)

    # Path separator.
    export PATH_SEP = \\

    # Function for create directories.
    MakeDir = md
else 
    # Executable.
    export EXEC = lc

    # Function for fixing path separator.
    FixPath = $1

    # Path separator.
    export PATH_SEP = /

    # Function for create directories.
    MakeDir = mkdir -p
endif

# Directories.
export ROOT_DIR  = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
export INC_DIR   = $(call FixPath,$(ROOT_DIR)/include)
export SRC_DIR   = $(call FixPath,$(ROOT_DIR)/src)
export BUILD_DIR = $(call FixPath,$(ROOT_DIR)/build)

# Compiler options.
export CXXFLAGS = -std=c++17 -I $(INC_DIR)

all:
	$(MakeDir) $(BUILD_DIR)
	cd $(SRC_DIR) && $(MAKE) all
