# Compiler and flags
CXX = g++
CFLAGS = -pthread -I../lib -O3 #-Wall -Werror -Wvla -mavx2
DEPFLAGS = -MMD -MP

# Directories
BUILD = ../build/src
SRCS_C = $(wildcard *.c)
SRCS_CPP = $(wildcard *.cpp)
OBJS_C = $(patsubst %.c, $(BUILD)/%.o, $(SRCS_C))
OBJS_CPP = $(patsubst %.cpp, $(BUILD)/%.o, $(SRCS_CPP))
OBJS = $(OBJS_C) $(OBJS_CPP)
DEPS = $(OBJS:.o=.d)


# Target
.PHONY: all clean
TARGET = $(BUILD)/runner

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CXX) $(OBJS) -o $@ $(CFLAGS)
	@echo "/src/ done"

# Compilation rule for C files (compile as C++)
$(BUILD)/%.o: %.c
	@mkdir -p $(BUILD)
	@echo "\t$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@"
	@$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@

# Compilation rule for C++ files
$(BUILD)/%.o: %.cpp
	@mkdir -p $(BUILD)
	@echo "\t$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@"
	@$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@

-include $(DEPS)

clean:
	@rm -f $(OBJS) $(DEPS) $(TARGET)
	@echo "/src/ clean"
