# Defining OS specific configs.
ifeq ($(OS), Windows_NT)
    # Executable.
    export EXEC = lc.exe

    # Function for fixing path separator.
    FixPath = $(subst /,\\,$1)

    # Function for create directories.
    MakeDir = md
else 
    # Executable.
    export EXEC = lc

    # Function for fixing path separator.
    FixPath = $1

    # Function for create directories.
    MakeDir = mkdir -p
endif

# Directories.
export INC_DIR   = $(call FixPath, $(CURDIR)/include)
export SRC_DIR   = $(call FixPath, $(CURDIR)/src)
export BUILD_DIR = $(call FixPath, $(CURDIR)/build)


# Compiler options.
export CXXFLAGS = -std=c++17 -I $(INC_DIR)

all:
	$(MakeDir) $(BUILD_DIR)
	cd $(SRC_DIR) && $(MAKE) all
