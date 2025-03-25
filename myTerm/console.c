#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

// Функция для заполнения памяти случайными значениями
void fillRandomMemory() {
    srand(time(NULL)); // Инициализация генератора случайных чисел
    for (int i = 0; i < MEMORY_SIZE; i++) {
        int randomValue = rand() % 65536; // Генерация случайного числа от 0 до 65535
        if (rand() % 2 == 0) { // Случайно делаем число отрицательным
            randomValue = -randomValue;
        }
        sc_memorySet(i, randomValue);
    }
}

// Функция для отображения памяти в шестнадцатеричном виде
void printMemoryHex() {
    printf("Memory contents (hex):\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        int value;
        sc_memoryGet(i, &value);
        if (value >= 0) {
            printf("+%04X ", value); // Положительное значение с знаком +
        } else {
            printf("-%04X ", -value); // Отрицательное значение с знаком -
        }
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// Функция для отображения редактируемой ячейки (например, первая ячейка)
void printEditableCell() {
    int value;
    sc_memoryGet(0, &value); // Получаем значение из первой ячейки памяти
    printf("Editable Cell (Address 0): ");
    if (value >= 0) {
        printf("+%04X\n", value);
    } else {
        printf("-%04X\n", -value);
    }
}

// Функция для вывода консоли с блоками памяти, регистров и других данных
void print_console(int current_cell) {
    // Очистка экрана
    mt_clrscr();

    // Вывод блока "Оперативная память"
    for (int i = 0; i < MEMORY_SIZE; i++) {
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
    // Очищаем экран
    mt_clrscr();

    // Инициализация памяти
    sc_memoryInit();

    // Заполнение памяти случайными значениями
    fillRandomMemory();

    // Установка значений в память
    sc_memorySet(0, -1);
    sc_memorySet(1, 16383);
    sc_memorySet(2, -1);
    sc_memorySet(3, -123);
    for (int i = 4; i < MEMORY_SIZE; i++) {
        sc_memorySet(i, i * 2);  // Пример заполнения памяти
    }

    // Установка флагов
    sc_regSet(FLAG_INVALID_COMMAND, 1);
    sc_regSet(FLAG_IGNORE_CLOCK, 1);

    // Установка аккумулятора
    sc_accumulatorSet(500);

    // Отображение памяти
    printMemoryHex();

    // Отображение редактируемой ячейки (первой ячейки)
    printEditableCell();

    // Отображение аккумулятора
    printAccumulator();

    // Отображение регистра флагов
    printFlags();

    // Отображение счетчика команд
    printCounters();

    int addresses[5] = {0x00, 0x01, 0x02, 0x03, 0x04};
    in_out(addresses);

    // Вывод панели команды
    printCommandPanel();

    // Вывод консоли (например, для ячейки 5)
    print_console(5);

    return 0;
}
