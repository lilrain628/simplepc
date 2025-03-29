ARFLAGS = rcs
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Директории и имена целей
LIB_DIR = mySimpleComputer
LIB_NAME = libmySimpleComputer.a
LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

# Основное приложение (console)
APP_NAME = console_app
APP_SRCS = $(filter-out %/pr01.c, $(shell find . -type f -name "*.c" | sort -u))
APP_OBJS = $(APP_SRCS:.c=.o)

# Тестовая программа (pr01)
TEST_NAME = test_program
TEST_SRCS = $(shell find . -type f -name "pr01.c" | sort -u)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Общие объектные файлы (без main-функций)
COMMON_SRCS = $(filter-out %/console.c %/pr01.c, $(shell find . -type f -name "*.c" | sort -u))
COMMON_OBJS = $(COMMON_SRCS:.c=.o)

.PHONY: all clean build run run_test help

all: $(APP_NAME) $(TEST_NAME)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(LIB_TARGET): $(COMMON_OBJS) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^
	ar -t $@

$(APP_NAME): $(APP_OBJS) $(LIB_TARGET)
	$(CC) $(CFLAGS) -o $@ $(APP_OBJS) -L$(LIB_DIR) -lmySimpleComputer

$(TEST_NAME): $(TEST_OBJS) $(LIB_TARGET)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS) -L$(LIB_DIR) -lmySimpleComputer

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(APP_NAME) $(TEST_NAME)

run: $(APP_NAME)
	./$(APP_NAME)

run_test: $(TEST_NAME)
	./$(TEST_NAME)

build: all

help:
	@echo "Доступные команды:"
	@echo "  make all        - Собрать все цели (по умолчанию)"
	@echo "  make console    - Собрать основное приложение"
	@echo "  make test       - Собрать тестовую программу"
	@echo "  make run        - Запустить основное приложение"
	@echo "  make run_test   - Запустить тестовую программу"
	@echo "  make clean      - Очистить проект"
	@echo "  make help       - Показать это сообщение"