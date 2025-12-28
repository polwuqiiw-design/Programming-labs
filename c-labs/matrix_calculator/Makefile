# Компилятор
CC = gcc

# Флаги компиляции
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -Ilib

# Флаги линковки
LDFLAGS = -lSDL2 -lSDL2_ttf -lcurl -lm

# Директории
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Исходники
SRC_FILES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/student.c \
	$(SRC_DIR)/file_io.c \
	$(SRC_DIR)/network.c \
	$(SRC_DIR)/gui.c \
	lib/cJSON.c

# Объектные файлы (ВАЖНО: без src внутри obj)
OBJ_FILES = \
	$(OBJ_DIR)/main.o \
	$(OBJ_DIR)/student.o \
	$(OBJ_DIR)/file_io.o \
	$(OBJ_DIR)/network.o \
	$(OBJ_DIR)/gui.o \
	$(OBJ_DIR)/cJSON.o

# Цель
TARGET = $(BIN_DIR)/student_system

# Цель по умолчанию
all: $(TARGET)

# Создание директорий
$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

# Линковка
$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

# Компиляция src/*.c
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Компиляция cJSON
$(OBJ_DIR)/cJSON.o: lib/cJSON.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
