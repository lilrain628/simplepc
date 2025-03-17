# Основные переменные
CFLAGS = -Wall -Wextra -Iinclude
CC = gcc
AR = ar
ARFLAGS = rcs

# Пути
LIB_DIR = mySimpleComputer
LIB_NAME = libmySimpleComputer.a
LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

SRCS = $(LIB_DIR)/reg.c $(LIB_DIR)/ram.c $(LIB_DIR)/deviceControl.c $(LIB_DIR)/input_output.c
OBJS = $(SRCS:.c=.o)
PR01_SRC = $(LIB_DIR)/pr01.c
PR01_OBJ = $(PR01_SRC:.c=.o)
PR01_TARGET = $(LIB_DIR)/pr01

# Цель по умолчанию
all: $(LIB_TARGET) $(PR01_TARGET)

# Сборка статической библиотеки
$(LIB_TARGET): $(OBJS)
	@echo "Создание библиотеки $@"
	$(AR) $(ARFLAGS) $@ $^
	@echo "Содержимое библиотеки:"
	ar -t $@

# Сборка программы
$(PR01_TARGET): $(PR01_OBJ) $(LIB_TARGET)
	@echo "Сборка программы $@"
	$(CC) $(CFLAGS) -o $@ $(PR01_OBJ) -L$(LIB_DIR) -lmySimpleComputer

# Компиляция объектных файлов
%.o: %.c
	@echo "Компиляция $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(LIB_TARGET) $(PR01_OBJ) $(PR01_TARGET)

# Запуск программы
run: $(PR01_TARGET)
	@echo "Запуск программы $(PR01_TARGET)"
	./$(PR01_TARGET)