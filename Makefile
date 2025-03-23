ARFLAGS = rcs
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

LIB_DIR = mySimpleComputer
LIB_NAME = libmySimpleComputer.a
LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

# Автоматический поиск всех .c файлов, кроме pr01.c (с удалением дубликатов)
SRCS = $(filter-out %/pr01.c, $(shell find . -type f -name "*.c" | sort -u))
OBJS = $(SRCS:.c=.o)

# Автоматический поиск pr01.c (с удалением дубликатов)
PR01_SRC = $(shell find . -type f -name "pr01.c" | sort -u)
PR01_OBJ = $(PR01_SRC:.c=.o)
PR01_TARGET = $(basename $(notdir $(PR01_SRC)))

all: $(LIB_TARGET) $(PR01_TARGET)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(LIB_TARGET): $(OBJS) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^
	ar -t $@

$(PR01_TARGET): $(PR01_OBJ) $(LIB_TARGET)
	$(CC) $(CFLAGS) -o $@ $(PR01_OBJ) -L$(LIB_DIR) -lmySimpleComputer

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_DIR)/ram
	rm -f $(OBJS) $(LIB_TARGET) $(PR01_OBJ) $(PR01_TARGET) memory.bin mySimpleComputer.lib 
	rm -rf $(LIB_DIR)/*.o $(LIB_DIR)/*.a $(LIB_DIR)/*.bin $(LIB_DIR)/*.lib

run: $(PR01_TARGET)
	./$(PR01_TARGET)

# Добавленные команды
build: all

help:
	@echo "Доступные команды:"
	@echo "  make build       - Собрать проект (библиотеку и программу)"
	@echo "  make clean       - Очистить проект (удалить сгенерированные файлы)"
	@echo "  make run         - Запустить программу"
	@echo "  make help        - Показать это сообщение"