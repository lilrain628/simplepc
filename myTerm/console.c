#include "../include/myTerm.h"
#include "../include/mySimpleComputer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Проверка, что поток вывода связан с терминалом
int is_terminal() {
    return isatty(STDOUT_FILENO);
}

// Проверка размера экрана
int check_screen_size() {
    int rows, cols;
    if (mt_getscreensize(&rows, &cols)) {
        return -1;
    }
    // Минимальные размеры экрана (примерные значения)
    if (rows < 30 || cols < 80) {
        return -1;
    }
    return 0;
}

// Вывод консоли
void print_console(int current_cell) {
    // Очистка экрана
    mt_clrscr();

    // Вывод блока "Оперативная память"
    for (int i = 0; i < 100; i++) {
        if (i == current_cell) {
            // Инверсный режим для текущей ячейки
            mt_setbgcolor(WHITE);
            mt_setfgcolor(BLACK);
        }
        printCell(i, DEFAULT, DEFAULT);
        if (i == current_cell) {
            mt_setdefaultcolor();
        }
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }

    // Вывод блока "Регистр флагов"
    printFlags();

    // Вывод блока "Аккумулятор"
    printAccumulator();

    // Вывод блока "Счетчик команд"
    printCounters();

    // Вывод блока "IN—OUT"
    for (int i = 0; i < 7; i++) {
        printTerm(i * 10, 0); // Примерные адреса
    }

    // Вывод блока "Команда"
    printCommand();
}

int main() {
    // Проверка потока вывода
    if (!is_terminal()) {
        fprintf(stderr, "Ошибка: вывод не связан с терминалом.\n");
        exit(1);
    }

    // Проверка размера экрана
    if (check_screen_size()) {
        fprintf(stderr, "Ошибка: размер экрана недостаточен.\n");
        exit(1);
    }

    // Инициализация памяти и регистров
    sc_memoryInit();
    sc_regInit();

    // Пример: установка значений в память
    for (int i = 0; i < 100; i++) {
        sc_memorySet(i, i + 0x1000);
    }

    // Вывод консоли
    print_console(5); // Пример: текущая ячейка с адресом 5

    return 0;
}