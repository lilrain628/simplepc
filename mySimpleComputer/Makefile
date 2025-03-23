ARFLAGS = rcs
CC = gcc
CFLAGS = -Wall -Wextra -I../include

LIB_DIR = .
LIB_NAME = libmySimpleComputer.a
LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

# Автоматический поиск всех .c файлов в mySimpleComputer
SRCS = $(shell find . -type f -name "*.c")
OBJS = $(SRCS:.c=.o)

# Поиск pr01.c в ../console
PR01_SRC = $(shell find ../console -type f -name "pr01.c" 2>/dev/null)
PR01_OBJ = $(PR01_SRC:.c=.o)
PR01_TARGET = ../console/$(basename $(notdir $(PR01_SRC)))

all: $(LIB_TARGET)

ifneq ($(PR01_SRC),)
all: $(PR01_TARGET)
endif

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(LIB_TARGET): $(OBJS) | $(LIB_DIR)
#	@echo "Создание библиотеки $@"
	$(AR) $(ARFLAGS) $@ $^
#	@echo "Содержимое библиотеки:"
	ar -t $@

ifneq ($(PR01_SRC),)
$(PR01_TARGET): $(PR01_OBJ) $(LIB_TARGET)
#	@echo "Сборка программы $@"
	$(CC) $(CFLAGS) -o $@ $(PR01_OBJ) -L$(LIB_DIR) -lmySimpleComputer
endif

%.o: %.c
#	@echo "Компиляция $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f ram
	rm -f $(OBJS) $(LIB_TARGET) $(PR01_OBJ) $(PR01_TARGET) memory.bin mySimpleComputer.lib 
	rm -rf *.o *.a *.bin *.lib

ifneq ($(PR01_SRC),)
run: $(PR01_TARGET)
#	@echo "Запуск программы $(PR01_TARGET)"
	./$(PR01_TARGET)
endif