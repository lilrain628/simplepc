#include "mySimpleComputer.h"
int sc_commandEncode(int sign, int command, int operand, int *value) {
    if (value == NULL || sign < 0 || sign > 1 || command < 0 || command > COMMAND_MASK || operand < 0 || operand > OPERAND_MASK) {
        return -1;
    }

    *value = (sign << 7) | (command << 0) | (operand << 8);
    return 0;
}

int sc_commandDecode(int value, int *sign, int *command, int *operand) {
    if (sign == NULL || command == NULL || operand == NULL) {
        return -1;
    }

    *sign = (value & SIGN_MASK) >> 7;
    *command = (value & COMMAND_MASK);
    *operand = (value >> 8) & OPERAND_MASK;
    return 0;
}

int sc_commandValidate(int command) {
    if (command < 0 || command > COMMAND_MASK) {
        return -1;
    }
    return 0;
}