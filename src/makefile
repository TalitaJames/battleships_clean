# Compiler and flags
CXX = g++
CFLAGS = -pthread -I../lib -O3 #-Wall -Werror -Wvla -mavx2
DEPFLAGS = -MMD -MP

# Directories
BUILD = ../build/src
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, $(BUILD)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

# Target
.PHONY: all clean
TARGET = $(BUILD)/runner.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CXX) $(OBJS) -o $@ $(CFLAGS)
	@echo "/src/ done"

$(BUILD)/%.o: %.c
	@mkdir -p $(BUILD)
	@echo "\t$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@"
	@$(CXX) -c $< $(CFLAGS) $(DEPFLAGS) -o $@

-include $(DEPS)

clean:
	@rm -f $(OBJS) $(DEPS) $(TARGET)
	@echo "/src/ clean"
