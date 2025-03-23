#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include <stdio.h>
int sc_mt_gotoXY(int x, int y) {
  char buffer[32];
  int len = snprintf(buffer, sizeof(buffer), "\033[%d;%dH", x, y);
  if (write(STDOUT_FILENO, buffer, len) == -1) {
      return -1;
  }
  return 0;
}

// Функция для вывода содержимого одной ячейки памяти с учетом цветов
void printCell(int address, enum colors fg, enum colors bg) {
    int value;
    if (sc_memoryGet(address, &value)) {
        printf("Invalid address.\n");
        return;
    }

    // Установка цветов
    mt_setfgcolor(fg);
    mt_setbgcolor(bg);

    // Вычисление позиции для вывода
    int row = address / 10 + 2; // Примерное расположение блока "Оперативная память"
    int col = (address % 10) * 5 + 2;

    // Перемещение курсора и вывод значения
    sc_mt_gotoXY(row, col);
    printf("%04X", value);

    // Сброс цветов
    mt_setdefaultcolor();
}

// Функция для вывода содержимого регистра флагов
void printFlags(void) {
    int flags[5];
    sc_regGet(FLAG_OVERFLOW, &flags[0]);
    sc_regGet(FLAG_DIVISION_BY_ZERO, &flags[1]);
    sc_regGet(FLAG_MEMORY_ERROR, &flags[2]);
    sc_regGet(FLAG_INVALID_COMMAND, &flags[3]);
    sc_regGet(FLAG_IGNORE_CLOCK, &flags[4]);

    // Перемещение курсора в блок "Регистр флагов"
    sc_mt_gotoXY(15, 2); // Примерное расположение
    printf("Flags: %c %c %c %c %c", flags[0] ? 'O' : '_', flags[1] ? 'D' : '_',
          flags[2] ? 'M' : '_', flags[3] ? 'I' : '_', flags[4] ? 'C' : '_');
}

// Функция для вывода декодированной команды
void printDecodedCommand(int value) {
    int sign, command, operand;
    if (sc_commandDecode(value, &sign, &command, &operand)) {
        // Перемещение курсора в блок "Редактируемая ячейка (формат)"
        sc_mt_gotoXY(18, 2); // Примерное расположение
        printf("Invalid command format.");
        return;
    }

    // Перемещение курсора
    sc_mt_gotoXY(18, 2);
    printf("Decoded command: %c %02X %02X", sign ? '-' : '+', command, operand);
}

// Функция для вывода значения аккумулятора
void printAccumulator(void) {
    int value;
    sc_accumulatorGet(&value);

    // Перемещение курсора в блок "Аккумулятор"
    sc_mt_gotoXY(20, 2); // Примерное расположение
    printf("Accumulator: %04X", value);
}

// Функция для вывода значения счетчика команд
void printCounters(void) {
    int value;
    sc_icounterGet(&value);

    // Перемещение курсора в блок "Счетчик команд"
    sc_mt_gotoXY(22, 2); // Примерное расположение
    printf("Instruction Counter: %04X", value);
}

// Функция для вывода строки в блок "IN—OUT"
void printTerm(int address, int input) {
    static int history[4] = {0}; // История последних 4 строк
    static int index = 0;

    // Обновление истории
    history[index] = address;
    index = (index + 1) % 4;

    // Перемещение курсора в блок "IN—OUT"
    sc_mt_gotoXY(24, 2); // Примерное расположение

    // Вывод истории
    for (int i = 0; i < 4; i++) {
        int pos = (index + i) % 4;
        if (input && i == 0) {
            printf("> %04X\n", history[pos]);
        } else {
            printf("  %04X\n", history[pos]);
        }
    }
}

// Функция для вывода декодированной команды из счетчика команд
void printCommand(void) {
    int address;
    sc_icounterGet(&address);

    int value;
    if (sc_memoryGet(address, &value)) {
        // Перемещение курсора в блок "Команда"
        sc_mt_gotoXY(26, 2); // Примерное расположение
        printf("! Invalid address.");
        return;
    }

    int sign, command, operand;
    if (sc_commandDecode(value, &sign, &command, &operand)) {
        // Перемещение курсора
        sc_mt_gotoXY(26, 2);
        printf("! Invalid command format.");
        return;
    }

    // Перемещение курсора
    sc_mt_gotoXY(26, 2);
    printf("Command: %c %02X %02X", sign ? '-' : '+', command, operand);
}