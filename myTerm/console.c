#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#define MEMORY_MAX_SIZE MEMORY_SIZE


void fillMemoryWithRandomValues(int count)
{
    srand(time(NULL)); // Инициализация генератора случайных чисел

    for (int i = 0; i < count && i < MEMORY_MAX_SIZE; i++)
    {
        int randomValue;

        // Заполняем только первые 10 ячеек
        if (i < 10)
        {
            if (i == 0)
            {
                randomValue = 16383; // Первая ячейка: 16383
            }
            else if (i == 1)
            {
                randomValue = -16384; // Вторая ячейка: -16384
            }
            else
            {
                // Генерация случайного числа от 0 до 32767
                randomValue = rand() % 32768;

                // Сдвигаем диапазон в отрицательную сторону, вычитая 16384
                randomValue -= 16384;
            }
        }
        else
        {
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

    // int addresses[5] = {0x00, 0x01, 0x02, 0x03, 0x04};
    // in_out(addresses);

    printCommandPanel();
    return 0;
}