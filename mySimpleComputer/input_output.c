#include "mySimpleComputer.h"

void printCell(int address) {
    int value;
    if (sc_memoryGet(address, &value)){
        printf("Invalid address.\n");
        return;
    }

    int sign, command, operand;
    if (sc_commandDecode(value, &sign, &command, &operand)) {
        printf("Invalid command format.\n");
        return;
    }

    printf("Cell %d: %c %02X %02X\n", address, sign ? '-' : '+', command, operand);
}

void printFlags(void) {
    int flags[5];
    sc_regGet(FLAG_OVERFLOW, &flags[0]);
    sc_regGet(FLAG_DIVISION_BY_ZERO, &flags[1]);
    sc_regGet(FLAG_MEMORY_ERROR, &flags[2]);
    sc_regGet(FLAG_INVALID_COMMAND, &flags[3]);
    sc_regGet(FLAG_IGNORE_CLOCK, &flags[4]);

    printf("Flags: %c %c %c %c %c\n",
    flags[0] ? 'O' : '_',
    flags[1] ? 'D' : '_',
    flags[2] ? 'M' : '_',
    flags[3] ? 'I' : '_',
    flags[4] ? 'C' : '_');
}

void printDecodedCommand(int value) {
    printf("Decoded command:\n");
    printf("Decimal: %d\n", value);
    printf("Octal: %o\n", value);
    printf("Hexadecimal: %X\n", value);
    printf("Binary: ");
    for (int i = 15; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
    printf("\n");
}

void printAccumulator(void) {
    int value;
    sc_accumulatorGet(&value);
    printf("Accumulator: %d\n", value);
}

void printCounters(void) {
    int value;
    sc_icounterGet(&value);
    printf("Instruction Counter: %d\n", value);
}