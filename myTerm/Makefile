CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I../include
LDFLAGS = -L. -lmyTerm -L../mySimpleComputer -lmySimpleComputer

# Цели
all: libmyTerm.a libmySimpleComputer.a console

# Сборка библиотеки myTerm
libmyTerm.a: myTerm.o
	ar rcs libmyTerm.a myTerm.o

# Компиляция myTerm.c
myTerm.o: myTerm.c ../include/myTerm.h
	$(CC) $(CFLAGS) -c myTerm.c -o myTerm.o

# Сборка библиотеки mySimpleComputer
libmySimpleComputer.a: mySimpleComputer.o
	ar rcs libmySimpleComputer.a mySimpleComputer.o

# Компиляция mySimpleComputer.c
mySimpleComputer.o: mySimpleComputer.c ../include/mySimpleComputer.h
	$(CC) $(CFLAGS) -c mySimpleComputer.c -o mySimpleComputer.o

# Сборка приложения console
console: console.c libmyTerm.a libmySimpleComputer.a
	$(CC) $(CFLAGS) console.c -o console $(LDFLAGS)

# Очистка
clean:
	rm -f *.o *.a console

.PHONY: all clean
