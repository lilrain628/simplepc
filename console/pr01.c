#include "mySimpleComputer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Константа для максимального размера памяти
#define MEMORY_MAX_SIZE 130

// Функция для заполнения памяти случайными значениями
void fillMemoryWithRandomValues(int count) {
    srand(time(NULL)); // Инициализация генератора случайных чисел
    for (int i = 0; i < count && i < MEMORY_MAX_SIZE; i++) {
        int randomValue = rand() % 65536; // Генерация случайного числа от 0 до 65535
        if (rand() % 2 == 0) {           // Случайно делаем число отрицательным
            randomValue = -randomValue;
        }
        sc_memorySet(i, randomValue);
    }
}

int main() {
    // a. Инициализация оперативной памяти, аккумулятора, счетчика команд и регистра флагов
    sc_memoryInit();
    sc_accumulatorInit();
    sc_icounterInit();
    sc_regInit();

    // b. Заполнение памяти случайными значениями (130 ячеек)
    fillMemoryWithRandomValues(MEMORY_MAX_SIZE);

    // Вывод содержимого памяти (в декодированном формате по 10 ячеек в строке через пробел)
    printf("Memory contents:\n");
    for (int i = 0; i < MEMORY_MAX_SIZE; i++) {
        int value;
        sc_memoryGet(i, &value); // Получаем значение из памяти
        if (value >= 0) {
            printf("+%04X ", value); // Положительное значение с знаком +
        } else {
            printf("-%04X ", -value); // Отрицательное значение с знаком -
        }
        if ((i + 1) % 10 == 0) printf("\n"); // Переход на новую строку каждые 10 ячеек
    }
    printf("\n");

    // c. Попытка задать недопустимое значение ячейке памяти
    int status = sc_memorySet(128, 0xFFFF); // Недопустимый адрес
    printf("Status of setting invalid memory address: %d\n", status);

    // d. Установка произвольных значений флагов и вывод содержимого регистра флагов
    sc_regSet(FLAG_OVERFLOW, 1);
    sc_regSet(FLAG_DIVISION_BY_ZERO, 1);
    printFlags();

    // e. Попытка установить недопустимое значение флага
    status = sc_regSet(0x20, 1); // Недопустимый флаг
    printf("Status of setting invalid flag: %d\n", status);

    // f. Установка значения аккумулятора и вывод на экран
    sc_accumulatorSet(42);
    printAccumulator();

    // g. Попытка задать аккумулятору недопустимое значение
    status = sc_accumulatorSet(-1); // Недопустимое значение
    printf("Status of setting invalid accumulator value: %d\n", status);

    // h. Установка значения счетчика команд и вывод на экран
    sc_icounterSet(10);
    printCounters();

    // i. Попытка задать счетчику команд недопустимое значение
    status = sc_icounterSet(128); // Недопустимое значение
    printf("Status of setting invalid instruction counter value: %d\n", status);

    // j. Декодирование значения произвольной ячейки памяти и значение аккумулятора
    int sign, command, operand;
    sc_commandDecode(0x1234, &sign, &command, &operand);
    printf("Decoded memory cell: sign=%d, command=%d, operand=%d\n", sign, command, operand);

    int accValue;
    sc_accumulatorGet(&accValue);
    printf("Decoded accumulator value: %d\n", accValue);

    // k. Кодирование команды и вывод полученного значения в разных системах счисления
    int encodedValue;
    sc_commandEncode(1, 10, 20, &encodedValue);
    printDecodedCommand(encodedValue);

    // Сохранение и загрузка памяти
    status = sc_memorySave("memory.bin");
    if (status == 0) {
        printf("Memory saved to memory.bin\n");
    } else {
        printf("Failed to save memory to memory.bin\n");
    }

    status = sc_memoryLoad("memory.bin");
    if (status == 0) {
        printf("Memory loaded from memory.bin\n");
    } else {
        printf("Failed to load memory from memory.bin\n");
    }

    // Повторный вывод флагов
    printFlags();

    return 0;
}