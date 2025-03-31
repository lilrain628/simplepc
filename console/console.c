#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#define MEMORY_MAX_SIZE MEMORY_SIZE

// Функция для заполнения памяти случайными значениями
void fillMemoryWithRandomValues(int count) {
    srand(time(NULL)); // Инициализация генератора случайных чисел

    for (int i = 0; i < count && i < MEMORY_MAX_SIZE; i++) {
        int randomValue;

        // Заполняем только первые 10 ячеек
        if (i < 10) {
            if (i == 0) {
                randomValue = 1; // Первая ячейка: 
            } else if (i == 1) {
                randomValue = -16384; // Вторая ячейка: -16384
            } else {
                // Генерация случайного числа от 0 до 32767
                randomValue = rand() % 32768;

                // Сдвигаем диапазон в отрицательную сторону, вычитая 16384
                randomValue -= 16384;
            }
        } else {
            // Остальные ячейки заполняем нулями
            randomValue = 0;
        }

        // Записываем значение в память
        sc_memorySet(i, randomValue);
    }
}

int main() {
    // Очищаем экран
    mt_clrscr();

    // Инициализация памяти
    sc_memoryInit();

    // Заполнение памяти случайными значениями
    fillMemoryWithRandomValues(MEMORY_MAX_SIZE);

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

    // Читаем значения из памяти для вывода IN-OUT
    int addresses[5] = {0x00, 0x020, 0x039, 0x040, 0x057};
    in_out(addresses);

    // Отображение панели "Команда"
    printCommandPanel();

    return 0;
}