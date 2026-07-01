# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall

# Flags de tracking de dependências
DEPFLAGS = -MMD -MP

# Diretórios de include
INCDIRS = acoes_menu auxiliares linkedlist partida time

# Adiciona automaticamente -I antes de cada diretório
INC_FLAGS = $(addprefix -I,$(INCDIRS))

# Diretório de build (onde ficarão os arquivos .o e .d)
BUILD_DIR = .build

# Arquivos fonte (todos os .c na raiz + pastas do INCDIRS)
SRCS = $(wildcard *.c) $(wildcard $(addsuffix /*.c, $(INCDIRS))) 

# Seleção de arquivos objeto e dependências correspondentes
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS = $(patsubst %.c,$(BUILD_DIR)/%.d,$(SRCS))

# Nome do executável final
TARGET = main

# Phony targets
.PHONY: all compile run clean

# Default target (Compile and run)
all: compile run

# Explicit compile target
compile: $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Limpa a pasta de build e o executável
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Compile source files into object files
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) $(DEPFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Inclui os arquivos de dependências, para o Make saber sobre mudanças nos headers (.h)
-include $(DEPS)