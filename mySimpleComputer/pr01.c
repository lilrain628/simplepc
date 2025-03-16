#include "mySimpleComputer.h"


int main() {
    //a
    sc_memoryInit();
    sc_accumulatorInit();
    sc_icounterInit();
    sc_regInit();

    //b
    sc_memorySet(0, 0x1234);
    sc_memorySet(1, 0x5678);
    sc_memorySet(2, 0x9ABC);
    sc_memorySet(3, 0xDEF0);
    sc_memorySet(4, 0x1111);
    sc_memorySet(5, 0x2222);
    sc_memorySet(6, 0x3333);
    sc_memorySet(7, 0x4444);
    sc_memorySet(8, 0x5555);
    sc_memorySet(9, 0x6666);

    printf("Memory contents:\n");
    for (int i = 0; i < 10; i++) {
        printCell(i);
        if ((i + 1) % 10 == 0) printf("\n");
    }

    // c
    int status = sc_memorySet(128, 0xFFFF);
    printf("Status of setting invalid memory address: %d\n", status);

    // d
    sc_regSet(FLAG_OVERFLOW, 1);
    sc_regSet(FLAG_DIVISION_BY_ZERO, 1);
    printFlags();

    // e
    status = sc_regSet(0x20, 1);
    printf("Status of setting invalid flag: %d\n", status);

    // f
    sc_accumulatorSet(42);
    printAccumulator();

    // g
    status = sc_accumulatorSet(-1);
    printf("Status of setting invalid accumulator value: %d\n", status);

    // h
    sc_icounterSet(10);
    printCounters();

    // i
    status = sc_icounterSet(128);
    printf("Status of setting invalid instruction counter value: %d\n", status);

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