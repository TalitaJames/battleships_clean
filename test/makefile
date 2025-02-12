# Compiler and flags
CXX = g++
CFLAGS = -pthread -I../lib -Ilib -O3 #-Wall -Werror -Wvla -mavx2
DEPFLAGS = -MMD -MP # makes a .d file in the build directory listing dependencies

# Directories
SRC_BUILD = ../build/src
TEST_BUILD = ../build/test

TEST_SRCS_C = $(wildcard src/*.c)
TEST_SRCS_CPP = $(wildcard src/*.cpp)
TEST_OBJS_C = $(patsubst src/%.c, $(TEST_BUILD)/%.o, $(TEST_SRCS_C))
TEST_OBJS_CPP = $(patsubst src/%.cpp, $(TEST_BUILD)/%.o, $(TEST_SRCS_CPP))
TEST_OBJS = $(TEST_OBJS_C) $(TEST_OBJS_CPP)
TEST_DEPS = $(TEST_OBJS:.o=.d)

# Exclude main.o from SRC_OBJS
SRC_OBJS = $(filter-out $(SRC_BUILD)/main.o, $(wildcard $(SRC_BUILD)/*.o))

# Target
.PHONY: all clean
TEST_TARGET = $(TEST_BUILD)/test_runner

all: $(TEST_TARGET)

# build test executable
$(TEST_TARGET): $(SRC_OBJS) $(TEST_OBJS)
	@mkdir -p $(TEST_BUILD)
	@$(CXX) $(SRC_OBJS) $(TEST_OBJS) -o $@ $(CFLAGS)
	@echo "/test/ done"

# Build any .o files from the test/src/ directory
$(TEST_BUILD)/%.o: src/%.c #compile .c as .cpp
	@mkdir -p $(TEST_BUILD)
	@echo "\t$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@"
	@$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@

$(TEST_BUILD)/%.o: src/%.cpp #compile .cpp
	@mkdir -p $(TEST_BUILD)
	@echo "\t$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@"
	@$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@

-include $(TEST_DEPS) # tells make which .o files depend on which headers

clean:
	@rm -f $(TEST_OBJS) $(TEST_DEPS) $(TEST_TARGET)
	@echo "/test/ clean"
