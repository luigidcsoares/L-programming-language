# Source files.
SRC = $(wildcard core/*.cpp) \
      $(wildcard lexer/*.cpp) \
      $(wildcard utils/*.cpp)

# Object files.
OBJ = $(SRC:.cpp=.o)

# Build object files from cpp source.
%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

all: $(OBJ)
	@echo "========== Starting compilation =========="
	$(CXX) $(OBJ) -o "$(BUILD_DIR)$(EXEC)"
