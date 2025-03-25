CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include
LDFLAGS = -L. -lmyTerm -L../mySimpleComputer -lmySimpleComputer

# Цели
all: libmyTerm.a console

# Сборка библиотеки myTerm
libmyTerm.a: myTerm.o
	ar rcs libmyTerm.a myTerm.o  # <-- ТАБУЛЯЦИЯ (не пробелы)

# Компиляция myTerm.c
myTerm.o: myTerm.c ../include/myTerm.h
	$(CC) $(CFLAGS) -c myTerm.c -o myTerm.o  # <-- ТАБУЛЯЦИЯ

# Сборка приложения console
console: console.c libmyTerm.a
	$(CC) $(CFLAGS) console.c -o console $(LDFLAGS)  # <-- ТАБУЛЯЦИЯ

# Очистка
clean:
	rm -f *.o *.a console  # <-- ТАБУЛЯЦИЯ

.PHONY: all clean  # <-- Исправлена опечатка (.PHYONY -> .PHONY)