# Compiler and flags
CXX = g++
CFLAGS = -pthread -I../lib -O3 #-Wall -Werror -Wvla -mavx2
DEPFLAGS = -MMD -MP

# Directories
BUILD = ../build/src
SRCS = $(wildcard *.c) $(wildcard *.cpp)
OBJS = $(patsubst %.c, $(BUILD)/%.o, $(SRCS)) # replace file.c into ../build/src/file.o
OBJS := $(patsubst %.cpp, $(BUILD)/%.o, $(OBJS))  # convert remaining .cpp into .o
DEPS = $(OBJS:.o=.d)

# Target
.PHONY: all clean
TARGET = $(BUILD)/runner.exe

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
