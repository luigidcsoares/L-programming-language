# Source files.
SRC = $(wildcard core/*.cpp) \
      $(wildcard lexer/*.cpp) \
      $(wildcard parser/*.cpp) \
      $(wildcard utils/*.cpp)

# Object files.
OBJ = $(SRC:.cpp=.o)

# Fixing path separator on windows.
ifeq ($(OS), Windows_NT)
	FixPath = $(subst /,\,$1)
else
	FixPath = $1
endif

# Build object files from cpp source.
%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

all: $(OBJ)
	$(CXX) $(OBJ) -o "$(BUILD_DIR)$(EXEC)"

clean:
	-$(RM) $(call FixPath,$(OBJ))
	-$(RM) "$(BUILD_DIR)$(EXEC)"
