#include "../include/myTerm.h"
#include "../include/mySimpleComputer.h"
#include <stdio.h>
#include <stdint.h>

#define RED_TEXT "\x1b[31m"
#define WHITE_BG "\x1b[47m"
#define WHITE_TEXT "\x1b[37m"
#define BLACK_BG "\x1b[40m"
#define RESET_COLORS "\x1b[0m"

void printMemoryHex() {
    printf("\x1b[2;1H");

    int value;
    sc_memoryGet(0, &value);
    printf(RED_TEXT WHITE_BG "%04X  " RESET_COLORS, value & 0xFFFF);

    printf(WHITE_TEXT BLACK_BG);
    for (int i = 1; i < MEMORY_SIZE; i++) {
        if (i % 10 == 0) {
            printf("\n\x1b[%d;1H", 2 + i / 10);
        }
        sc_memoryGet(i, &value);
        printf("%c%04X  ", (value & 0x8000) ? '-' : '+', value & 0xFFFF);
    }
    printf(RESET_COLORS "\n");
}
void printDecodedCommand(int command) {
    // Пример: декодирование и вывод команды в формате "+XX : YY"
    int opcode = (command >> 7) & 0x1F; // Получаем код операции (5 бит)
    int operand = command & 0x7F;       // Получаем операнд (7 бит)
    printf("+%02X : %02X\n", opcode, operand);
}
void printAccumulator() {
    mt_gotoXY(2, 75);
    printf(RED_TEXT BLACK_BG "Аккумулятор\n");
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    int acc;
    sc_accumulatorGet(&acc);
    mt_gotoXY(3, 70);
    printf("(SC): %+d  | Hex: %04X \n", acc, acc & 0x7FFF);
    mt_setdefaultcolor();
}

void printFlags() {
    mt_gotoXY(2, 110);
    printf(RED_TEXT BLACK_BG "Регистр флагов\n");
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    int p, zero, m, t, e;
    sc_regGet(FLAG_OVERFLOW, &p);
    sc_regGet(FLAG_INVALID_COMMAND, &zero);
    sc_regGet(FLAG_MEMORY_ERROR, &m);
    sc_regGet(FLAG_IGNORE_CLOCK, &t);
    e = 0;

    mt_gotoXY(3, 100);
    printf("Flags:| %c | %c | %c | %c | %c |\n",
           p ? 'P' : '_', zero ? '0' : '_', m ? 'M' : '_', t ? 'T' : '_', e ? 'E' : '_');
    mt_setdefaultcolor();
}

void printCounters() {
    mt_gotoXY(5, 75);
    printf(RED_TEXT BLACK_BG "Счетчик команд\n");
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    int ic;
    sc_icounterGet(&ic);

    mt_gotoXY(6, 70);
    printf("T:00 IC:%04X \n", ic & 0x7FFF);
    mt_setdefaultcolor();
    mt_gotoXY(30, 1);
}

void in_out(int addresses[5]) {
    printf("\x1b[20;1H");
    printf(RED_TEXT BLACK_BG "Ввод-вывод\n");
    printf(WHITE_TEXT BLACK_BG);

    for (int i = 0; i < 5; i++) {
        int address = addresses[i];
        if (address < 0 || address >= MEMORY_SIZE) {
            printf("Адрес %02X недопустим\n", address);
            continue;
        }

        int value;
        sc_memoryGet(address, &value);
        printf("%02X> %c%04X\n", address, (value & 0x8000) ? '-' : '+', value & 0x7FFF);
    }
    printf(RESET_COLORS);
}

void printCommandPanel() {
    mt_gotoXY(8, 75);
    printf(RED_TEXT BLACK_BG "Команда\n");
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    mt_gotoXY(9, 70);
    
    // Получаем текущую команду (например, из памяти или регистра)
    int currentCommand;
    sc_memoryGet(sc_icounterGet(NULL), &currentCommand);
    printDecodedCommand(currentCommand); // Выводим декодированную команду

    mt_setdefaultcolor();
    mt_gotoXY(30, 1);
}