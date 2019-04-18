# Defining OS specific configs.
ifeq ($(OS), Windows_NT)
    # Executable.
    export EXEC = lc.exe

    # Path separator.
    export PATH_SEP = \\
else 
    # Executable.
    export EXEC = lc

    # Path separator.
    export PATH_SEP = /
endif

# Directories.
export INC_DIR   = $(CURDIR)$(PATH_SEP)include
export SRC_DIR   = $(CURDIR)$(PATH_SEP)src
export BUILD_DIR = $(CURDIR)$(PATH_SEP)build

# Compiler options.
export CXXFLAGS = -std=c++17 -I $(INC_DIR)

all:
	mkdir -p $(BUILD_DIR)
	cd $(SRC_DIR) && $(MAKE) all
