

ARFLAGS = rcs
LIB_DIR = mySimpleComputer
LIB_NAME = libmySimpleComputer.a
LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

SRCS = reg.c ram.c deviceControl.c input_output.c  
OBJS = $(SRCS:.c=.o)
PR01_SRC = pr01.c
PR01_OBJ = $(PR01_SRC:.c=.o)
PR01_TARGET = pr01

all: $(LIB_TARGET) $(PR01_TARGET)


$(LIB_DIR):
	mkdir -p $(LIB_DIR)


$(LIB_TARGET): $(OBJS) | $(LIB_DIR)
	@echo "Создание библиотеки $@"
	$(AR) $(ARFLAGS) $@ $^
	@echo "Содержимое библиотеки:"
	ar -t $@


$(PR01_TARGET): $(PR01_OBJ) $(LIB_TARGET)
	@echo "Сборка программы $@"
	gcc -o $@ $(PR01_OBJ) -L$(LIB_DIR) -lmySimpleComputer


%.o: %.c
	@echo "Компиляция $<"
	gcc  -c $< -o $@


clean:
	rm -f $(OBJS) $(LIB_TARGET) $(PR01_OBJ) $(PR01_TARGET)
	rm -rf $(LIB_DIR)


run: $(PR01_TARGET)
	@echo "Запуск программы $(PR01_TARGET)"
	./$(PR01_TARGET)