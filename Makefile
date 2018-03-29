# Variáveis de comando
CC = gcc
CFLAGS = -Wall -g

# Diretórios
SRC_DIR = src/
BIN_DIR = bin/
OBJ_DIR = obj/

# Arquivos
SOURCES = $(wildcard $(SRC_DIR)*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)%.c= $(OBJ_DIR)%.o)
TARGET = $(addprefix $(BIN_DIR), cobrinha)

# Alvo main (executável)
main: $(OBJECTS) $(BIN_DIR)
	$(CC) -g $(OBJECTS) -o $(TARGET)

# Gera arquivos objeto
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

# Cria diretório de binários
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Cria diretórios de objetos
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Remove arquivos gerados
clean:
	$(RM) $(OBJECTS) $(TARGET)
