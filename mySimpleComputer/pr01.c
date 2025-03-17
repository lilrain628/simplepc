#include "mySimpleComputer.h"

int main() {
    // a
    sc_memoryInit();
    sc_accumulatorInit();
    sc_icounterInit();
    sc_regInit();

    // b
    sc_memorySet(0, 0x1234);
    sc_memorySet(1, 0x5678);
    sc_memorySet(2, 0x9ABC);

    printf("Memory contents:\n");
    for (int i = 0; i < 130; i++) { // Выводим 13 строк по 10 ячеек
        printCell(i);
        if ((i + 1) % 10 == 0) printf("\n"); // Переход на новую строку после каждых 10 ячеек
    }

    // c
    int status = sc_memorySet(128, 0xFFFF); // Попытка установить значение за пределами допустимого диапазона
    if (status == -1) {
        printf("Status of setting invalid memory address: -1\n");
    } else {
        printf("Status of setting invalid memory address: %d\n", status);
    }

    // d
    sc_regSet(FLAG_OVERFLOW, 1);
    sc_regSet(FLAG_DIVISION_BY_ZERO, 1);
    printFlags();

    // e
    status = sc_regSet(0x20, 1); // Попытка установить недопустимый флаг
    if (status == -1) {
        printf("Status of setting invalid flag: -1\n");
    } else {
        printf("Status of setting invalid flag: %d\n", status);
    }

    // f
    sc_accumulatorSet(42);
    printAccumulator();

    // g
    status = sc_accumulatorSet(-1); // Попытка установить недопустимое значение аккумулятора
    if (status == -1) {
        printf("Status of setting invalid accumulator value: -1\n");
    } else {
        printf("Status of setting invalid accumulator value: %d\n", status);
    }

    // h
    sc_icounterSet(10);
    printCounters();

    // i
    status = sc_icounterSet(128); // Попытка установить недопустимое значение счетчика команд
    if (status == -1) {
        printf("Status of setting invalid instruction counter value: -1\n");
    } else {
        printf("Status of setting invalid instruction counter value: %d\n", status);
    }

    // j
    int sign, command, operand;
    sc_commandDecode(0x1234, &sign, &command, &operand);
    printf("Decoded memory cell: sign=%d, command=%d, operand=%d\n", sign, command, operand);

    int accValue;
    sc_accumulatorGet(&accValue);
    printf("Decoded accumulator value: %d\n", accValue);

    // k
    int encodedValue;
    sc_commandEncode(1, 10, 20, &encodedValue);
    printDecodedCommand(encodedValue);

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

    printFlags();

    return 0;
}