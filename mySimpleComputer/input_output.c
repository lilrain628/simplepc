#include "../include/myTerm.h"
#include "../include/mySimpleComputer.h"
#include <stdio.h>
#include <stdint.h>

#define RED_TEXT "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define WHITE_BG "\x1b[47m"
#define WHITE_TEXT "\x1b[37m"
#define BLACK_BG "\x1b[40m"
#define RESET_COLORS "\x1b[0m"

int memory[MEMORY_SIZE];
// Функция для отображения памяти
void printMemoryHex() {
    printf("\x1b[2;1H");  // Перемещаем курсор на 2 строку, 1 столбец

    // Первая ячейка: красный текст на белом фоне
    printf(RED_TEXT WHITE_BG "%04X  " RESET_COLORS, memory[0] & 0xFFFF);  // Маска для 16 бит

    // Остальные ячейки: белый текст на черном фоне
    printf(WHITE_TEXT BLACK_BG);
for (int i = 1; i < MEMORY_SIZE; i++) {
    if (i % 10 == 0) {  // Переход на новую строку каждые 10 ячеек
        printf("\n\x1b[%d;1H", 2 + i / 10);  // Перемещаем курсор на новую строку
    }

    // Проверяем знаковый бит (15-й бит)
    if (memory[i] & 0x8000) {  // Если знаковый бит установлен
        printf("-");  // Отрицательное число
    } else {
        printf("+");  // Положительное число
    }

    // Выводим значение в формате %04X (16-битное шестнадцатеричное число)
    printf("%04X  ", memory[i] & 0xFFFF);  // Маска для 16 бит
}
printf(RESET_COLORS "\n");  // Сбрасываем цвета
}

// Функция для отображения редактируемой ячейки
void printEditableCell() {
    printf("\x1b[17;1H");  // Перемещаем курсор на 17 строку, 1 столбец

    printf(RED_TEXT WHITE_BG "Редактируемая ячейка (формат)\n");
    // Редактируемая ячейка: красный текст на белом фоне

    // Приводим memory[0] к знаковому типу
    int16_t signed_value = (int16_t)(memory[0] & 0xFFFF);

    printf(WHITE_TEXT BLACK_BG "dec: %d  | oct: %o  | hex: %04X   bin: ", signed_value, signed_value, signed_value & 0xFFFF);
    for (int i = 14; i >= 0; i--) {  // 15 бит (знак + 14 бит данных)
        printf("%d", (signed_value >> i) & 1);
    }
    printf(RESET_COLORS "\n");
}

// Функция для отображения аккумулятора
void printAccumulator() {
    mt_gotoXY(2, 75);  // Позиция для вывода аккумулятора
    printf(RED_TEXT BLACK_BG "Аккумулятор\n");
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    int acc;
    sc_accumulatorGet(&acc);

    mt_gotoXY(3, 75);
    printf("sc: %+d    hex: %04X \n", acc, acc & 0x7FFF);
    mt_setdefaultcolor();
}

// Функция для отображения регистра флагов
void printFlags() {
    mt_gotoXY(2, 110);  // Позиция для вывода флагов
    printf(RED_TEXT BLACK_BG "Регистр флагов\n");
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    int p, zero, m = 0, t, e;
    sc_regGet(FLAG_OVERFLOW, &p);
    sc_regGet(FLAG_DIVISION_BY_ZERO, &zero);
    sc_regGet(FLAG_MEMORY_ERROR, &m);
    sc_regGet(FLAG_INVALID_COMMAND     , &t);
    sc_regGet(FLAG_IGNORE_CLOCK        , &e);

    mt_gotoXY(3, 110);
    printf("%c   %c   %c   %c   %c ",
    p ? 'P' : '_', zero ? '0' : '_', m ? 'M' : '_', t ? 'T' : '_', e ? 'E' : '_');
    printf("\n");
    mt_setdefaultcolor();
}

// Функция для отображения счетчика команд
void printCounters() {
    mt_gotoXY(5, 75);
    printf(RED_TEXT BLACK_BG "Счетчик команд\n");
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    int ic;
    sc_icounterGet(&ic);

    mt_gotoXY(6, 75);
    printf("T:00      IC:%04X \n", ic & 0x7FFF);
    mt_setdefaultcolor();

    mt_gotoXY(30, 1);
}

// Функция для отображения панели "Команда"
void printCommandPanel() {
    mt_gotoXY(5, 115);  // Позиция для вывода панели "Команда"
    printf(RED_TEXT BLACK_BG "Команда\n");
    mt_setfgcolor(WHITE);
    mt_setbgcolor(BLACK);

    // Пример команды в формате "+ 00 : 01"
    mt_gotoXY(6, 115);
    printf("+ 00 : 01\n");

    mt_setdefaultcolor();
    mt_gotoXY(30, 1);
}

void in_out(int addresses[5]) {
    printf("\x1b[20;1H");  // Перемещаем курсор на 20 строку, 1 столбец
    
    // Заголовок: зеленый текст на белом фоне
    printf(GREEN_TEXT WHITE_BG "IN--OUT" RESET_COLORS "\n");
    
    for (int i = 0; i < 5; i++) {
        int address = addresses[i];
        if (address < 0 || address >= MEMORY_SIZE) {
            printf("Адрес %02X недопустим\n", address);
            continue;
        }

        // Получаем значение ячейки памяти
        int16_t value = (int16_t)(memory[address] & 0xFFFF);

        // Определяем знак значения
        char sign = (value & 0x8000) ? '-' : '+';

        // Включаем белый фон только для выводимого текста
        printf(BLACK_BG "%02X> %c%04X" RESET_COLORS "\n", 
               address, sign, value & 0x7FFF);
    }
}
void printDecodedCommand(int value) {
    int sign, command, operand;
    sc_commandDecode(value, &sign, &command, &operand);
    
    printf("Decoded command:\n");
    printf("Sign: %s\n", sign ? "-" : "+");
    printf("Command: %d (0x%X)\n", command, command);
    printf("Operand: %d (0x%%X)\n", operand, operand);
}
