# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Define the directories
INCDIRS = auxiliares partida tabela_classificacao tabelas time

# Automatically add -I before each directory
INC_FLAGS = $(addprefix -I,$(INCDIRS))

# Source files
SRCS = $(wildcard *.c) $(wildcard $(addsuffix /*.c, $(INCDIRS))) 

# Object files
OBJS = $(patsubst %.c,%.o,$(SRCS))

# Executable name
TARGET = main

# Phony targets
.PHONY: all compile run clean

# Default target (compile and run)
all: compile run

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)