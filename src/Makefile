# Source files.
SRC = $(wildcard core$(PathSep)*.cpp) \
      $(wildcard lexer$(PathSep)*.cpp) \
      $(wildcard parser$(PathSep)*.cpp) \
      $(wildcard utils$(PathSep)*.cpp)

# Object files.
OBJ = $(SRC:.cpp=.o)

# Build object files from cpp source.
%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

all: $(OBJ)
	@echo "========== Starting compilation =========="
	$(CXX) $(OBJ) -o "$(BUILD_DIR)$(EXEC)"

clean:
	-$(RM) $(OBJ)
	-$(RM) "$(BUILD_DIR)$(EXEC)"
