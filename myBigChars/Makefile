CC = gcc
CFLAGS = -Wall -Iinclude

# Объекты для компиляции
PROGS = $(wildcard mySimpleComputer/*.c) $(wildcard myBigChars/*.c) $(wildcard myTerm/*.c) $(wildcard console/*.c)
OBJS = $(PROGS:.c=.o)

# Указываем путь к библиотеке
LIBRARY = libmySimpleComputer.a

# Основная цель
all: $(OBJS) $(LIBRARY)

# Создаём статическую библиотеку
$(LIBRARY): $(OBJS)
	ar -rcs $@ $(OBJS)

# Компиляция исходников в объектные файлы
%.o: %.c
	$(CC) $(CFLAGS) -c -g -o $@ $<

# Форматирование исходных файлов
format:
	find . -type f -name '*.[ch]' | xargs clang-format --style=GNU -i --verbose

# Очистка сгенерированных файлов
clean:
	rm -rf $(OBJS)
	rm -rf $(LIBRARY)
