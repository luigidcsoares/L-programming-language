# Source files.
SRC = $(wildcard core/*.cpp) \
      $(wildcard lexer/*.cpp)

# Object files.
OBJ = $(SRC:.cpp=.o)

# Build object files from cpp source.
%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

all: $(OBJ)
	@echo $(OBJ)
	$(CXX) $(OBJ) -o $(BUILD_DIR)/$(EXEC)
