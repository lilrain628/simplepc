CC = gcc
CFLAGS = -Wall

INCLUDEDIR = ../include

LIB = mySimpleComputer
LIB1 = myTerm
LIB2 = myBigChars

LIBDIR = ../mySimpleComputer
LIBDIR1 = ../myTerm
LIBDIR2 = ../myBigChars

PROGS = $(wildcard *.c)
OBJS = $(PROGS:.c=.o)

FONT = font
APP = pr01

all: $(SRC) $(APP) $(FONT)

$(APP): $(OBJS)
	$(CC) -g -o $@ $(OBJS) -L$(LIBDIR) -L$(LIBDIR1) -L$(LIBDIR2) -l$(LIB) -l$(LIB2) -l$(LIB1) -lm

%.o : %.c
	$(CC) $(CFLAGS) -c -g -o $@ $< -I$(INCLUDEDIR) 

$(FONT): fontik/font.c
	$(CC) $^ -o $@ -L$(LIBDIR2) -l$(LIB2) -lm -I$(INCLUDEDIR)
format:
	find . -type f -name '*.[ch]' | xargs clang-format --style=GNU -i --verbose
run:
	./$(FONT)
	./$(APP)
clean:
	rm -rf $(OBJS)
	rm -rf $(APP)
	rm -rf $(FONT)
	rm -rf font.bin


