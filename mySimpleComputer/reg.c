#include "mySimpleComputer.h"
static int accumulator = 0;
static int instruction_counter = 0;
static int flag_register = 0;

int sc_regInit(void) {
    flag_register = 0;
    return 0;
}

int sc_regSet(int reg, int value) {
    if (reg != FLAG_OVERFLOW &&
        reg != FLAG_DIVISION_BY_ZERO &&
        reg != FLAG_MEMORY_ERROR &&
        reg != FLAG_INVALID_COMMAND &&
        reg != FLAG_IGNORE_CLOCK) {
        return -1;
    }

    if (value) {
        flag_register |= reg;
    } else {
        flag_register &= ~reg;
    }
    return 0;
}

int sc_regGet(int reg, int *value) {
    if ((reg != FLAG_OVERFLOW &&
        reg != FLAG_DIVISION_BY_ZERO &&
        reg != FLAG_MEMORY_ERROR &&
        reg != FLAG_INVALID_COMMAND &&
        reg != FLAG_IGNORE_CLOCK )||
        value == NULL) {
        return -1;
    }

    *value = (flag_register & reg) ? 1 : 0;
    return 0;
}

int sc_accumulatorInit(void) {
    accumulator = 0;
    return 0;
}

int sc_accumulatorSet(int value) {
    accumulator = value;
    return 0;
}

int sc_accumulatorGet(int *value) {
    if (value == NULL) {
        return -1;
    }
    *value = accumulator;
    return 0;
}

int sc_icounterInit(void) {
    instruction_counter = 0;
    return 0;
}

int sc_icounterSet(int value) {
    if (value < 0 || value >= 128) {
        return -1;
    }
    instruction_counter = value;
    return 0;
}

int sc_icounterGet(int *value) {
    if (value == NULL) {
        return -1;
    }
    *value = instruction_counter;
    return 0;
}