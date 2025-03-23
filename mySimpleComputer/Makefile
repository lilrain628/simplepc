# Основные переменные
ARFLAGS = rcs
CC = gcc
CFLAGS = -Wall -Wextra -I../include

# Пути
LIB_DIR = .
LIB_NAME = libmySimpleComputer.a
LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

# Автоматический поиск всех .c файлов в текущей директории
SRCS = $(shell find . -type f -name "*.c")
OBJS = $(SRCS:.c=.o)

# Цель по умолчанию
all: $(LIB_TARGET)

# Создание каталога для библиотеки (если нужно)
$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Сборка статической библиотеки
$(LIB_TARGET): $(OBJS) | $(LIB_DIR)
	@echo "Создание библиотеки $@"
	$(AR) $(ARFLAGS) $@ $^
	@echo "Содержимое библиотеки:"
	ar -t $@

# Компиляция объектных файлов
%.o: %.c
	@echo "Компиляция $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	@echo "Очистка временных файлов"
	rm -f ram
	rm -f $(OBJS) $(LIB_TARGET) memory.bin mySimpleComputer.lib
	rm -rf *.o *.a *.bin *.lib